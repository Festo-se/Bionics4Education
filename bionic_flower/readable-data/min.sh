MINIFIER_NAME="css-html-js-minify"

if ! [ -x "$(command -v $MINIFIER_NAME)" ]; then
  echo 'ERROR: $MINIFIER_NAME is not installed. Please install using `pip install $MINIFIER_NAME` or `pip3 install $MINIFIER_NAME`' >&2
  exit 1
fi

echo "--- DELETE `data` FOLDER ---"

rm -r ../data

echo "--- COPY FILES FROM `readable-data` TO `data` ---"

cp -r . ../data

echo "--- CHANGE DIRECTORY TO `data` ---"

cd ../data

echo "--- MINIFY JS FILES ---"

css-html-js-minify js --overwrite --quiet
cat js/jquery.min.js > script.min.js
rm js/jquery.min.js
cat js/bootstrap.min.js >> script.min.js
rm js/bootstrap.min.js
cat js/bootstrap-slider.min.js >> script.min.js
rm bootstrap-slider.min.js
cat js/*.js >> script.min.js
rm -r js

echo "--- MINIFY CSS FILES ---"

css-html-js-minify css --overwrite --quiet
cat css/bootstrap.min.js > styles.min.css
rm css/bootstrap.min.js
cat css/bootstrap-slider.min.js >> styles.min.css
rm css/bootstrap-slider.min.js
cat css/*.css >> styles.min.css
rm -r css

echo "--- MINIFY HTML FILES ---"

css-html-js-minify index.htm --quiet
rm index.htm

echo "--- CLEAN UP ---"

rm min.sh
cd ../readable-data

echo "--- DONE ---"
