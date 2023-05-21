import { contextBridge, ipcRenderer } from 'electron'

contextBridge.exposeInMainWorld('electron', {
    saveToDisk: (path: string, data: string) => {
        ipcRenderer.invoke('saveToDisk', path, data)
    }
})
