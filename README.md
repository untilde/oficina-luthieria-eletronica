## Running
```
npm install
npm run dev
```

## Estrutura do Vue App
```
app/
├── config
│   ├── eslint.config.ts
│   ├── tsconfig.app.json
│   ├── tsconfig.node.json
│   ├── tsconfig.vitest.json
│   └── vitest.config.ts
├── docs
│   ├── SLIDES.md
│   └── TODO.md
├── env.d.ts
├── index.html
├── node_modules
├── public
│   └── favicon.ico
├── src
│   ├── App.vue
│   ├── assets
│   ├── main.ts
│   ├── router
│   ├── slides
│   ├── stores
│   ├── __tests__
│   └── views
├── tsconfig.app.json
└── tsconfig.vitest.json
```

## Estrutura dos slides
```
app/src/slides/
├── 1_intro
│   ├── 01_SlideIntro.vue
│   ├── 02_SlideAbout.vue
│   └── 03_SlideEquipe.vue
├── 2_synth_hist
│   └── 01_SlideSynthHist1.vue
├── 3_som
│   └── 01_SlideSom1.vue
├── 4_synth_struct
│   └── 01_SlideSynth1.vue
├── 5_mozzi
│   └── 01_SlideMozzi1.vue
├── 6_dsp
└── registry.ts <--------- configura a ordenação automática dos slides
```


