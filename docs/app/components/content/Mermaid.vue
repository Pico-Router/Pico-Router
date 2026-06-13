<script setup lang="ts">
import mermaid from 'mermaid'

const el = ref<HTMLElement | null>(null)
const source = ref('')
const colorMode = useColorMode()

const theme = computed(() => colorMode.value === 'dark' ? 'dark' : 'default')

const renderDiagram = async () => {
  if (!el.value || !source.value) {
    return
  }

  mermaid.initialize({
    startOnLoad: false,
    theme: theme.value
  })

  const id = `mermaid-${Math.random().toString(36).slice(2)}`
  const { svg } = await mermaid.render(id, source.value)
  el.value.innerHTML = svg
}

onMounted(async () => {
  source.value = el.value?.textContent?.trim() || ''
  await renderDiagram()
})

watch(theme, async () => {
  await renderDiagram()
})
</script>

<template>
  <div
    ref="el"
    class="mermaid"
  >
    <slot />
  </div>
</template>
