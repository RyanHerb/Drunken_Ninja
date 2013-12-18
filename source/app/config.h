#ifndef CONFIG_H
#define CONFIG_H

#ifdef _WIN32
const string DEFAULT_DIRECTORY = "../data/";
const string DEFAULT_INPUT = "../data/tree1.txt";
#else
const string DEFAULT_DIRECTORY = "../../data/";
const string DEFAULT_INPUT = "../../data/tree1.txt";
#endif //_WIN32

#endif // CONFIG_H
