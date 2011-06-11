:: requires mxmlc in PATH;
:: tested with Open Source Flex SDK 4.5 (MIT) http://opensource.adobe.com/wiki/display/flexsdk/Download+Flex+4.5

mxmlc -library-path+=libs/stringecho.swc --target-player=10.2 --optimize=true -static-link-runtime-shared-libraries --debug=false --default-script-limits 5000 60 --advanced-anti-aliasing=true  src/EchoTest.mxml -o Test.swf