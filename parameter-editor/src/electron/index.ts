import { app, BrowserWindow  } from 'electron'

function createWindow() {
    const appWindow = new BrowserWindow()
    appWindow.webContents.openDevTools()
    appWindow.loadFile('index.html')
}

app.on('window-all-closed', () => {
    app.quit()
})

app.whenReady().then(createWindow)
