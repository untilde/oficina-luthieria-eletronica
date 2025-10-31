import { describe, it, expect } from 'vitest'
import { mount } from '@vue/test-utils'
import App from '../App.vue'
import router from '../router'

describe('App', () => {
  it('renders SlideView with navigation', async () => {
    router.push('/1')
    await router.isReady()
    const wrapper = mount(App, {
      global: { plugins: [router] },
    })
    // Should render the first slide title and navigation buttons
    expect(wrapper.text()).toContain('DSP para Iniciantes')
    expect(wrapper.find('button[aria-label="Anterior"]').exists()).toBe(true)
    expect(wrapper.find('button[aria-label="Próximo"]').exists()).toBe(true)
  })
})
