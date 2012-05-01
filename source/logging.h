////////////////////////////////////////////////////////
// logging.nxc
//
// Generic and useful logging functions

//
// Requires you to supply LOGFILE and LOGFILE_SIZE
// and define the global boolean LOGGING to true/false
//
// Copyright (c) September 2011, Mark Crosbie
// mark@mastincrosbie.com
// http://www.mastincrosbie.com/Marks_LEGO_projects
////////////////////////////////////////////////////////

int handle;

// 
// Open the log file
//
void openLogFile(string filename, int filesize) {
	int bw;
	string s;
	
	if(!LOGGING) 
		return;
		
	DeleteFile(filename);
	int r = CreateFile(filename, filesize, handle);

	WriteString(handle, "Logfile opened at ", bw);
	s = FormatNum("%d ticks", CurrentTick());
	WriteLnString(handle, s, bw);
}

void writeLogString(string s) {

	int bw;
	string m;
	
	if(!LOGGING)
		return;
	
	m = FormatNum("%d,", CurrentTick());
	m = m + s;
	WriteLnString(handle, m, bw);	
}

void writeLogByte(byte b) {

	int bw;
	string m;
	
	if(!LOGGING)
		return;
		
	m = FormatNum("%d : ", CurrentTick());
	m = m + FormatNum("%d", b);
	WriteLnString(handle, m, bw);	
}

void writeLogBytes(byte b[]) {

	int bw, i, length;
	string m;
	
	if(!LOGGING)
		return;
	
	length = SizeOf(b);
	
	m = FormatNum("%d : ", CurrentTick());
	WriteString(handle, m, bw);	
	for(i=0; i < length; i++) {
		m = FormatNum("%0x ", b[i]);
		WriteString(handle, m, bw);	
	}
	WriteLnString(handle, " ", bw);
}

void writeLogValue(string name, int value) {

	string s;
	
	if(!LOGGING)
		return;	
	
	s = name + FormatNum(" = %d", value);
	writeLogString(s);
}

void writeLogValue2(string name, int value1, int value2) {

	string s;
	
	if(!LOGGING)
		return;	
	
	s = name + FormatNum(" = %d,  ", value1);
	s = s + FormatNum("%d", value2);
	writeLogString(s);
}

void writeLogValue3(string name, int value1, int value2, int value3) {

	string s;
	
	if(!LOGGING)
		return;	
	
	s = name + FormatNum(" = %d,  ", value1);
	s = s + FormatNum("%d,  ", value2);
	s = s + FormatNum("%d", value3);
	writeLogString(s);
}

void writeLogValue5(float value1, float value2, float value3, float value4, float value5) {
	
	string s;
	
	if(!LOGGING)
		return;	
	
	s = FormatNum("%.5f,", value1);
	s = s + FormatNum("%.5f,", value2);
	s = s + FormatNum("%.5f,", value3);
	s = s + FormatNum("%.5f,", value4);
	s = s + FormatNum("%.5f", value5);
	writeLogString(s);
}

void closeLogFile() {
	int bw;
	string s;
	
	if(!LOGGING) 
		return;
		
	LOGGING = false;
	WriteString(handle, "Logfile closed at ", bw);
	s = FormatNum("%d ticks", CurrentTick());
	WriteLnString(handle, s, bw);	
	
	CloseFile(handle);
}
