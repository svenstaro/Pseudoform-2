#include "Managers/LogManager.hpp"

LogManager::LogManager()
{
    mDefaultPath = "Engine.log";
}

void LogManager::_forceLog(const string& logPath)
{
    if (std::find(mUsedFiles.begin(), mUsedFiles.end(), logPath) == mUsedFiles.end())
    {
        if (boost::filesystem::exists(logPath))
            boost::filesystem::remove(logPath);
        mUsedFiles.push_back(logPath);
    }
}

string LogManager::getCurrentTime(){
    ptime time = microsec_clock::local_time();
    return to_simple_string(time);
}

void LogManager::setDefaultLog(const string& logPath)
{
    mDefaultPath = logPath;
}

string LogManager::_cleanSignature(const string &signature)
{
	// Remove template stuff from signature. The string like: "type Class::function(arguments) [with ...]"
	// The goal is to make that string: Class::Function()
	// We really don't need arguments list and template insertion
	string result = signature;

	// Remove function return type
	int typePosition = result.find(" ");
	result = result.erase(0, typePosition+1); // Now we have "Class::function(arguments) [with ...]"

	// Remove function arguments and template stuff
	int argPosition = result.find("(");
	result = result.erase(argPosition);     // Now we have "Class::function"
	result += "()";

	return result;
}

void LogManager::write(const string& message, const string logFile, const string metaSignature)
{
    string workPath = mDefaultPath;
    if (logFile != "") workPath = logFile;

    this->_forceLog(workPath);

    string comand = "";
    if (metaSignature != "")
    {
    	string signature = _cleanSignature(metaSignature);
    	comand += getCurrentTime() + " : [";
    	comand += signature;
    	comand += "]\n[Message] ";
    	comand += message;
    	comand += "\n---------------------------------------------------------\n";
    }
    else
    {
    	comand += getCurrentTime() + "\t: " + message + "\n";
    }

    mLogHandle.open(workPath.c_str(), fstream::app | fstream::ate);
    mLogHandle << comand;
    mLogHandle.close();
}
