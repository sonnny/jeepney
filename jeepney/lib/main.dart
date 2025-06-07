/*******************************************
 * add location permission to android/app/src/main/AndroidManifest.xml
 *
 * <uses-permission android:name="android.permission.BLUETOOTH_SCAN"/>
 * <uses-permission android:name="android.permission.BLUETOOTH_CONNECT" />
 * <uses-permission android:name="android.permission.ACCESS_FINE_LOCATION" />
 *
 ***********************************************/

import 'package:flutter/material.dart';
import './jeepney.dart';

void main() {runApp(const MainApp());}

class MainApp extends StatelessWidget {
const MainApp({super.key});

@override Widget build(BuildContext context) {
  return MaterialApp(debugShowCheckedModeBanner: false,
    title: 'jeepney', home: Jeepney());}}
