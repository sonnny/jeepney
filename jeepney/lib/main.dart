import 'package:flutter/material.dart';
import './jeepney.dart';

void main() {runApp(const MainApp());}

class MainApp extends StatelessWidget {
const MainApp({super.key});

@override Widget build(BuildContext context) {
  return MaterialApp(debugShowCheckedModeBanner: false,
    title: 'jeepney', home: Jeepney());}}
