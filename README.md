# oficina-luthieria

## Project Setup

```sh
npm install
```

### Compile and Hot-Reload for Development

```sh
npm run dev
```

### Type-Check, Compile and Minify for Production

```sh
npm run build
```

### Run Unit Tests with [Vitest](https://vitest.dev/)

```sh
npm run test:unit
```

### Lint with [ESLint](https://eslint.org/)

```sh
npm run lint

## Project layout

- Runtime app lives under `app/` (Vite root)
	- `app/index.html`, `app/src`, `app/public`, `app/env.d.ts`
- Build output goes to root-level `dist/`
- Tooling stays at the repo root: `vite.config.ts`, `vitest.config.ts`, `eslint.config.ts`, `tsconfig.json`

Aliasing: `@` maps to `app/src` in both Vite and TypeScript.
```
