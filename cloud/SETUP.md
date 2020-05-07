# Setup steps

Summary steps to get going

## 1. Install Firebase tools
``` npm install -g firebase-tools ```

## 2. Associate Google Project with Firebase

1. Navigate to https://console.firebase.google.com
1. Choose `Add a project`
1. Select our project (e.g `Home IOT`)
1. If running for the first time you might be taken through an obvious setup
   wizard. Probably don't need analytics

## 3. Initialize Firebase

1. Navigate to this folder (`cloud`)
1. ``` firebase login ```
1. ``` firebase init ```
1. Select `Database`, `Functions`, `Hosting` and confirm
1. Select `Use an existing project` and confirm
1. Choose the default database rules filename (we already have that file in place locally)
1. Choose to *NOT* overwrite our existing file
1. Choose `Javascript` for cloud functions
1. Choose to *NOT* use ESLINT (we can do that in our own IDE)
1. Choose to *NOT* overwrite existing index.js file
1. Choose to install dependencies now
1. Choose to use default `public` folder as public directory (it already exists)
1. Choose to *NOT* confirgure as a single-page app
1. Choose to *NOT* overwrite existing files
