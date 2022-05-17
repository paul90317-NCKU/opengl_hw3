#include "objLoader.hpp"
#include "comm.hpp"
#include <cstdlib>
using namespace std;

#define num_format(c) ((c > '9' || c < '0')&&c!='.'&&c!='-')

vector<GLfloat> splitf(char* line, int count) {
	vector<GLfloat> ret;
	for (; num_format(line[0]); line = line + 1);
	for (int i = 0; i < count; i++)
		ret.push_back(strtof(line, &line));
	return ret;
}
vector<int> spliti(char* line) {
	vector<int> ret;
	for (; num_format(line[0]); line = line + 1);
	for (int i = 0; line[i]; i++)
		if (line[i] == '/')
			line[i] = ' ';
	for (int i = 0; i < 9; i++)
		ret.push_back(strtol(line, &line, 10) - 1);
	return ret;
}

int objLoader(const char* filename, vector<GLfloat> &posf, vector<GLfloat> &norf, vector<GLfloat> &texf, vector<GLuint> &posi, vector<GLuint> &nori, vector<GLuint> &texi) {
	fstream fs;
	static char buf[10000];
	fs.open(filename);
	vector<float> tmpf;
	vector<int> tmpi;
	while (fs.getline(buf, sizeof(buf)),buf[0]) {
		switch (buf[0]) {
		case 'v':
			switch (buf[1]) {
			case 'n':
				tmpf = splitf(buf, 3);
				for(int i=0;i<3;i++)
					norf.push_back(tmpf[i]);
				break;
			case ' ':
				tmpf = splitf(buf, 3);
				for(int i=0;i<3;i++)
					posf.push_back(tmpf[i]);
				break;
			case 't':
				tmpf = splitf(buf, 2);
				for(int i=0;i<2;i++)
					texf.push_back(tmpf[i]);
				break;
			}
			break;
		case 'f':
			tmpi = spliti(buf);
			for (int i = 0; i < 3; i++) {
				posi.push_back(tmpi[3 * i + 0]);
				texi.push_back(tmpi[3 * i + 1]);
				nori.push_back(tmpi[3 * i + 2]);
			}
			break;
		default:
			continue;
		}
	}
	fs.close();
	return posi.size();
}

int ToBuffer(vector<GLfloat>& allf, vector<GLfloat>& posf, vector<GLfloat>& norf, vector<GLfloat>& texf, vector<GLuint>& posi, vector<GLuint>& nori, vector<GLuint>& texi) {
	int count = posi.size();
	allf.resize(count * 8);
	int w;//which element
	for (int i = 0; i < count; i++) {
		w = posi[i];
		for (int j = 0; j < 3; j++)
			allf[8 * i + j] = posf[3 * w + j];
		w = nori[i];
		for (int j = 0; j < 3; j++)
			allf[8 * i + 3 + j] = norf[3 * w + j];
		w = texi[i];
		for (int j = 0; j < 2; j++)
			allf[8 * i + 6 + j] = texf[2 * w + j];
	}
	return count;
}


