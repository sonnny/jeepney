import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'dart:io';
import 'dart:convert';
import 'dart:typed_data';
import 'package:flutter_joystick/flutter_joystick.dart';
import 'package:flutter_blue_plus/flutter_blue_plus.dart';

TextStyle connectedStyle = TextStyle(color:Colors.blue,fontSize:18,fontWeight:FontWeight.bold);

TextStyle notConnectedStyle = TextStyle(color:Colors.red);

//use nrf connect to find info
const String BLE_ADDRESS = '2C:CF:67:E6:3B:A3';
const String SERVICE = '112233445566778899aabbccddeeff00';
const String CHARACTERISTIC = 'CAFE';

class Jeepney extends StatefulWidget{
  Jeepney({super.key});
  @override State<Jeepney> createState() => JeepneyState();}
  
class JeepneyState extends State<Jeepney>{

Key key = UniqueKey();
late BluetoothDevice device;
String? status = 'connect';
bool isConnected = false;
var txCharacteristic;

void sendData(data) async {
  String? temp = "";
  int x = (data.x * 100).toInt();
  int y = (data.y * 100).toInt();
  temp = "speed " + x.toString() + " " + y.toString();
  try{ List<int>? toSend = utf8.encode(temp);
    await txCharacteristic.write(toSend, withoutResponse: true);}
  catch (e){}}
  
//create a bluetooth device from ble address
//connect device without scan
//discover services
//assign transmit characteristic
//update status text
void connect()async{
  device = BluetoothDevice(remoteId:DeviceIdentifier(BLE_ADDRESS));
  await device.connect();//connect without bluetooth scan
  List<BluetoothService> services = await device.discoverServices();
  txCharacteristic = BluetoothCharacteristic(
    remoteId: device.remoteId,
    serviceUuid: Guid(SERVICE),
    characteristicUuid: Guid(CHARACTERISTIC));
  setState((){status = 'ready'; isConnected = true;});}

@override Widget build(BuildContext context){
return Scaffold(appBar: AppBar(title: Text('Jeepney')),
    
body: Column(children:[

////////////////////////////////////////////////////
//start 1st column
Padding(padding:EdgeInsets.fromLTRB(20,20,0,0),
child:Text('Notes:',style:TextStyle(color:Colors.purple,fontSize:20,
fontWeight:FontWeight.bold))),

//////////////////////////////////////////////////
//start 2nd column
Padding(padding:EdgeInsets.all(10), 
child:Text('''make sure ble device is on
update AndroidManifest.xml with location
permissions and allowed this app with location
permissions on settings''')),
         
///////////////////////////////////////////////////
//start 3rd column with a row
Padding(padding: EdgeInsets.all(10), child:Row(children:[

Text('ble address: '),

Text('${BLE_ADDRESS} ',style:TextStyle(fontSize:16)),

SizedBox(width:5),

ElevatedButton(child:Text('${status}',style: isConnected ? connectedStyle : notConnectedStyle), onPressed:() => connect(),)
])),//end 3rd column with rown
 
////////////////////////////////////////////////////////
//start 4th column with a row and within that row another column of buttons
Padding(padding:EdgeInsets.all(30), child:Row(children:[ 
   
Joystick(key: key, base: JoystickBase(
decoration: JoystickBaseDecoration(
color: Colors.lightBlue.shade600,drawArrows: true,
drawOuterCircle: true),
arrowsDecoration: JoystickArrowsDecoration(
color: Colors.grey.shade200,enableAnimation: false),
mode: JoystickMode.all),    
listener: (details){ sendData(details);}),
       
SizedBox(width:40),
          
Column(spacing:50,children:[
  //todo
  Text('stop'),
  Text('lights'),
  ElevatedButton(child:Text('exit'),//exit button
    onPressed:() async {
      await device.disconnect();
      SystemNavigator.pop();})])  
]))//end 4th column with row and within row another column of buttons
    
]));}}
    
    
 
      
              
