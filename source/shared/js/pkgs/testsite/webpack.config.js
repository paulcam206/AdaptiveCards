const path = require("path");
const HtmlWebpackPlugin = require('html-webpack-plugin');
const CopyWebpackPlugin = require('copy-webpack-plugin');

module.exports = (env, argv) => {
	const mode = argv.mode || 'development';
	const devMode = mode === "development";

	console.info('running webpack with mode:', mode);

	return {
		mode: mode,
		entry: {
			"main": "./src/index.tsx"
		},
		output: {
			path: path.resolve(__dirname, "./dist"),
			filename: devMode ? "[name].js" : "[name].min.js"
		},
		devtool: devMode ? "inline-source-map" : "source-map",
		devServer: {
			contentBase: './dist'
		},
		resolve: {
			extensions: [".ts", ".tsx", ".js", ".wasm"]
		},
		module: {
			rules: [{
				test: /\.tsx?$/,
				loader: "ts-loader",
				exclude: /(node_modules|__tests__)/
			}]
		},
		plugins: [
			new HtmlWebpackPlugin(),
            new CopyWebpackPlugin({
                patterns: [
                    {
                        from: "src/sample.json",
                        to: "hostConfig.json"
                    }
                ]
            })
		]
	}
}
