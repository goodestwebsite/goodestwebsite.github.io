/* Service worker for Audio Playlist.
 * Bump VERSION whenever you update index.html so clients pick it up. */
const VERSION = 'v1';
const CACHE = 'audio-playlist-' + VERSION;
const SHELL = ['./', './index.html'];

self.addEventListener('install', (e) => {
  e.waitUntil((async () => {
    const c = await caches.open(CACHE);
    // Add individually so one miss doesn't abort the whole install.
    await Promise.all(SHELL.map((u) =>
      c.add(new Request(u, { cache: 'reload' })).catch(() => {})
    ));
    await self.skipWaiting();
  })());
});

self.addEventListener('activate', (e) => {
  e.waitUntil((async () => {
    const keys = await caches.keys();
await self.clients.claim();
    await Promise.all(
      keys.filter((k) => k !== CACHE && k.startsWith('audio-playlist-'))
          .map((k) => caches.delete(k))
    );
    await self.clients.claim();
  })());
});

self.addEventListener('fetch', (e) => {
  const req = e.request;
  if (req.method !== 'GET') return;

  const url = new URL(req.url);
  // Don't touch blob:/data:/cross-origin requests (audio, artwork, etc.).
  if (url.origin !== self.location.origin) return;
  if ('serviceWorker' in navigator) {
    window.addEventListener('load', () => {
      navigator.serviceWorker.register('./sw.js', { scope: './' })
        .catch(() => {});
    });
  }
  // Page loads: serve cached shell instantly, refresh in background.
  if (req.mode === 'navigate') {
    e.respondWith((async () => {
      const cache = await caches.open(CACHE);
      const cached =
        (await cache.match(req, { ignoreSearch: true })) ||
        (await cache.match('./')) ||
        (await cache.match('./index.html'));

      const network = fetch(req).then((res) => {
        if (res && res.ok) cache.put(req, res.clone()).catch(() => {});
        return res;
      }).catch(() => null);

      return cached || (await network) ||
        new Response('Offline', { status: 503, headers: { 'Content-Type': 'text/plain' } });
    })());
    return;
  }

  // Everything else same-origin: stale-while-revalidate.
  e.respondWith((async () => {
    const cache = await caches.open(CACHE);
    const cached = await cache.match(req);

    const network = fetch(req).then((res) => {
      if (res && res.status === 200) cache.put(req, res.clone()).catch(() => {});
      return res;
    }).catch(() => null);

    return cached || (await network) || new Response('', { status: 504 });
  })());
});
