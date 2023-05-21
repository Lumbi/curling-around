import { app, BrowserWindow, ipcMain  } from 'electron'
import fs from 'fs/promises'
import path from 'path'

function createWindow() {
    const appWindow = new BrowserWindow({
        webPreferences: {
            preload: path.join(__dirname, 'preload.js')
        }
    })

    ipcMain.handle('saveToDisk', async (_, path, data) => {
        await fs.writeFile(path, data, 'utf-8')
    })

    appWindow.loadFile('index.html')
}

app.on('window-all-closed', () => {
    app.quit()
})

app.whenReady().then(createWindow)
