all:
	echo ""; echo "sharedLib building..."; echo "";
	cd ./sharedLib; make deploy; cd ../;
	echo ""; echo "testApp_withMinusL building"; echo "";
	cd ./testApp_withMinusL; make deploy; cd ../;
	echo ""; echo "testApp_withoutMinusL building"; echo "";
	cd ./testApp_withoutMinusL; make deploy; cd ../;
	
clean:
	cd ./sharedLib; make clean; cd ../;
	cd ./testApp_withMinusL; make clean; cd ../;
	cd ./testApp_withoutMinusL; make clean; cd ../;
	rm -rf ./demoApp
