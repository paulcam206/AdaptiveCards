const path = require("path");

// todo: dts-bundle for prod builds (see https://medium.com/@vladimirtolstikov/how-to-merge-d-ts-typings-with-dts-bundle-and-webpack-e8903d699576)

module.exports = (env, argv) => {
	const mode = argv.mode || 'development';
	const devMode = mode === "development";

	console.info('running webpack with mode:', mode);
	return {
		mode: mode,
	  entry: {
            main: path.resolve(__dirname, "./src/index.ts")
        },
		output: {
			path: path.resolve(__dirname, "./dist"),
			filename: devMode ? "[name].js" : "[name].min.js",
		    library: "adaptivecards-sharedmodel",
		    libraryTarget: "umd",
            umdNamedDefine: true
		    //   globalObject: "this",
		},
        resolve: {
            extensions: [ ".ts", ".tsx", ".js" ],
            fallback: {
                "path": false
            }
        },
	    devtool: devMode ? "inline-source-map" : "source-map",
      	module: {
			rules: [
                {
                    test: /\.tsx?$/,
                    loader: "ts-loader"
                },
                {
                    test: /\.wasm$/,
                    type: 'asset/resource'
                    // type: "javascript/auto",
                    // loader: "file-loader",
                    // options: {
                    //     publicPath: "./dist"
                    // }
                }
            ]
		}
    }
}
