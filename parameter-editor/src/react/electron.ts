export {}

declare global {
    interface Window {
        electron?: {
            saveToDisk: (path: string, data: string) => void
        }
    }
}