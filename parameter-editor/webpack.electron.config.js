const path = require('path')

const isProduction = process.env.NODE_ENV == 'production'

const config = {
  entry: '/src/electron/index.ts',
  output: {
    path: path.resolve(__dirname, 'dist'),
    filename: 'electron.js'
  },
  target: 'electron-renderer',
  devtool: 'source-map',
  module: {
    rules: [
      {
        test: /\.(ts|tsx)$/i,
        loader: 'ts-loader',
        exclude: ['/node_modules/'],
      },
      {
        test: /\.(html)$/,
        use: ['html-loader']
      },
    ],
  },
  resolve: {
    extensions: ['.tsx', '.ts', '.jsx', '.js', '...']
  }
};

module.exports = () => {
  if (isProduction) {
    config.mode = 'production'
  } else {
    config.mode = 'development'
  }
  return config
}
