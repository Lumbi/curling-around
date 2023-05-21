const path = require('path')
const HtmlWebpackPlugin = require('html-webpack-plugin')

const isProduction = process.env.NODE_ENV == 'production'

const stylesHandler = 'style-loader'

const config = {
  entry: '/src/react/index.tsx',
  output: {
    path: path.resolve(__dirname, 'dist'),
    filename: 'bundle.js'
  },
  target: 'web',
  devtool: 'source-map',
  module: {
    rules: [
      {
        test: /\.(ts|tsx)$/i,
        loader: 'ts-loader',
        exclude: ['/node_modules/'],
      },
      {
        test: /\.less$/i,
        use: [stylesHandler, 'css-loader', 'postcss-loader', 'less-loader'],
      },
      {
        test: /\.css$/i,
        use: [stylesHandler, 'css-loader', 'postcss-loader'],
      },
      {
        test: /\.(eot|svg|ttf|woff|woff2|png|jpg|gif)$/i,
        type: 'asset',
      },
      {
        test: /\.(html)$/,
        use: ['html-loader']
      },
    ],
  },
  resolve: {
    extensions: ['.tsx', '.ts', '.jsx', '.js', '...']
  },
  plugins: [
    new HtmlWebpackPlugin({
        template: path.resolve(__dirname, 'src/react/index.html'),
        filename: 'index.html'
    })
  ]
};

module.exports = () => {
  if (isProduction) {
    config.mode = 'production'
  } else {
    config.mode = 'development'
  }
  return config
}
