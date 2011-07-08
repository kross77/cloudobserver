:: requires mxmlc in PATH;
:: tested with Open Source Flex SDK 4.5.1 (MIT) http://opensource.adobe.com/wiki/display/flexsdk/Download+Flex+4.5

mxmlc  -library-path+=libs/as3crypto-1_3_patched.swc  -library-path+=libs/corelib-20070830.swc  -library-path+=libs/flexunit-20071226.swc  --target-player=10.2 --optimize=true -static-link-runtime-shared-libraries --debug=false --default-script-limits 5000 60 --advanced-anti-aliasing=true  src/player.mxml -o player.swf