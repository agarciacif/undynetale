import { defineConfig } from 'vite'

export default defineConfig({
    base: '/JuegoNDS/',
    build: {
        rollupOptions: {
            external: ['/dist/desmond.min.js']
        }
    }
})