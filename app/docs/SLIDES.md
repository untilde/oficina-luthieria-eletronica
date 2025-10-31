### Estrutura dos slides

Inserir slides usando a estrutura seguinte:

```
slides/
  1_intro/
    01_SlideIntro.vue
    02_SlideAbout.vue
    03_SlideEquipe.vue
  2_synth_hist/
    01_SlideSynthHist1.vue
```

O registry.ts automaticamente atualiza a ordem dos slides e headers no menu (app/src/slides/registry.ts):

```text
1. Intro
1.1 Slide name

2. Breve História...
2.1. Slide name
```

### Nomes de Seções e Slides

- Seções: Editar o objeto `sectionNameOverrides` em `app/src/slides/registry.ts`.

Exemplo:

- Pasta: `4_synth_struct/`
- Título desejado: `Estrutura básica de um Sintetizador`
- Em `registry.ts`:

  ```ts
  const sectionNameOverrides = {
    '4_synth_struct': 'Estrutura básica de um Sintetizador',
  }
  ```

- Slides: defina o título manualmente dentro do componente `.vue` exportando uma constante `slideTitle` (ou `title`). Use um `<script>` normal (não `<script setup>`):

  ```vue
  <script setup lang="ts">
  // lógica do componente
  </script>
  <script lang="ts">
  export const slideTitle = 'Meu Título do Slide'
  // Alternativamente: export const title = 'Meu Título do Slide'
  </script>
  ```

  O registry dará preferência a `slideTitle` (ou `title`) e, na ausência, cairá no título inferido a partir do nome do arquivo.
