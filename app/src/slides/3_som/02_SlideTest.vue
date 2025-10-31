<script setup lang="ts"></script>
<script lang="ts">
export const slideTitle = 'Visualizadores de Som'
export default {}
</script>

<template>
  <div class="w-full h-full flex flex-col items-center justify-center">
    <h3 class="text-2xl md:text-4xl font-semibold mb-2 text-center">Visualizadores Interativos</h3>
    <p class="mb-12">
      To Do: corrigir scaling das frequências no gráfico (clicar em 5khz me dá 2khz - bug)
    </p>
    <div class="w-full max-w-6xl mx-auto grid grid-cols-1 md:grid-cols-2 gap-8 px-2 md:px-4">
      <section class="flex flex-col items-center">
        <h4 class="text-base md:text-lg text-slate-300 mb-2 text-center">Figura 1. Onda Sonora</h4>
        <PhysicalWave />
      </section>

      <section class="flex flex-col items-center">
        <h4 class="text-base md:text-lg text-slate-300 mb-2 text-center">
          Figura 2. Ouça uma Senoide
        </h4>
        <SineListen />
      </section>
    </div>
  </div>
</template>

<script setup lang="ts">
import PhysicalWave from '@/components/visualizers/PhysicalWave.vue'
import SineListen from '@/components/visualizers/SineListen.vue'
</script>

<style scoped></style>
