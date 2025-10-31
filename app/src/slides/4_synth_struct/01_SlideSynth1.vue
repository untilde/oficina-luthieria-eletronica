<script setup lang="ts"></script>
<script lang="ts">
// Custom slide title used by the menu and header
export const slideTitle = 'Parte 1'
export default {}
</script>

<template>
  <div class="w-full h-full flex flex-col items-center justify-center text-center">
    <h3 class="text-3xl md:text-5xl font-semibold">Estrutura de um sintetizador</h3>

    <div class="slide-p text-left">
      <ul>
        <li>Osciladores (sine, saw, square, noise, etc.) (EXEMPLO INTERATIVO)</li>
        <li>Tipos de Síntese (EXEMPLOS DE ÁUDIO)</li>
        <li>Filtros (LPF, HPF, BP, etc.)</li>
        <li>CV/Gate e Voltage-Controlled Amplifiers (VCAs)</li>
        <li>Triggers e Envelopes</li>
        <li>Clock (EXEMPLO INTERATIVO)</li>
        <li>Low Frequency Oscillators (LFOs) (EXEMPLO INTERATIVO)</li>
      </ul>
    </div>
  </div>
</template>

<style scoped></style>
