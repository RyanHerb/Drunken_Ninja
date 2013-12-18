#ifndef CONFIG_H
#define CONFIG_H

#ifdef _WIN32
<<<<<<< HEAD
const string DEFAULT_DIRECTORY = "../data/";
const string DEFAULT_INPUT = "../data/tree1.txt";
#else
const string DEFAULT_DIRECTORY = "../../data/";
const string DEFAULT_INPUT = "../../data/tree1.txt";
=======
const string DEFAULT_OUTPUT_DIRECTORY = "../../out/";
const string DEFAULT_INPUT_DIRECTORY = "../../data/";
const string DEFAULT_INPUT = "../../data/graph1.txt";
#else
const string DEFAULT_OUTPUT_DIRECTORY = "../../../out/";
const string DEFAULT_INPUT_DIRECTORY = "../../../data/";
const string DEFAULT_INPUT = "../../../data/graph1.txt";
>>>>>>> b54423ea15fb9a682a93e3fcdf736d5cacb7bccb
#endif //_WIN32

#endif // CONFIG_H
