// cpplearn.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <hash_map>
#include <unordered_map> 

using namespace std;
using std::vector;
using std::list;

vector<int> twoSum(vector<int> &numbers, int target) {
    vector<int> vInts;
	vector<int>::iterator it;
	int index1, index2;
	int x, y, tmp, xfound, yfound;
	vector<int> b(numbers);

	sort(b.begin(), b.end());

	vInts.clear();
	it = vInts.begin();

	index1 = 0;
	index2 = b.size() - 1;

	do {
		x =	b.at(index1);
		y = b.at(index2);

		if (x + y == target || x == y) break;
		if (x + y < target) index1++;
		else index2--;
	} while (1);

	if (x + y == target) {
		xfound = yfound = 0;
		for (unsigned int i = 0; i < numbers.size(); i++) {
			if (x == numbers.at(i) && !xfound) {
				index1 = i + 1;
				xfound = 1;
				continue;
			}
			if (y == numbers.at(i) && !yfound) {
				index2 = i + 1;
				yfound = 1;
				continue;
			}
		}

		if (index1 > index2) {
			tmp = index1;
			index1 = index2;
			index2 = tmp;
		}


		it = vInts.insert(it, index2);
		it = vInts.insert(it, index1);
	}
	else {
		it = vInts.insert(it, 0);
		it = vInts.insert(it, 0);
	}

	return vInts;
}

double findMedianSortedArrays(int A[], int m, int B[], int n) {
	int *C = new int[m+n];
	int i, j, k;

	i = j = 0; k = 0;
	do {
		if (i == m && j < n) {
			C[k] = B[j];
			j++;
			k++;
			continue;
		}
		if (j == n && i < m) {
			C[k] = A[i];
			i++;
			k++;
			continue;
		}
		if (k == m + n) break;

		if (A[i] < B[j]) {
			C[k] = A[i];
			i++;
		}
		else {
			C[k] = B[j];
			j++;
		}
		k++;
		
	} while (1); 

	double result;
	if (k % 2 == 0) result =  (double)(C[k/2] + C[k/2 -1])/2;
	else result = (double)C[(k - 1)/2];

	delete C;
	return result;
}

int lengthOfLongestSubstring(string s) {
	int maxlen, curlen;
	int sp, ep;
	int flag[256];
	unsigned char c, d;

	maxlen = s.length();
	if (maxlen < 2) return maxlen;

	for (int i = 0; i < 256; i++) {
		flag[i] = -1;
	}

	maxlen = 1;
	curlen = 1;
	sp = 0; ep = 0;
	c = s.at(sp);
	flag[c] = sp;

	do {
		ep++;
		if (ep == s.length()) break;
		d = s.at(ep);
		if (flag[d] < sp) {
			flag[d] = ep;
			curlen ++;
			if (curlen > maxlen) maxlen = curlen;
		}
		else {
			sp = flag[d] + 1;
			flag[d] = ep;
			curlen = ep - sp + 1;
		}
		
	} while(1);

	return maxlen;
}

/* for add Two Numbers*/
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    ListNode *s = new ListNode(0);
	ListNode *c;
	ListNode *n;

	ListNode *x1, *x2;
	int r, flag;

	x1 = l1; x2 = l2; flag = 0;
	c = s;

	while (x1 != NULL || x2 != NULL) {
		if (x1 != NULL && x2 != NULL) {
			r = x1->val + x2->val + flag;
			
			x1 = x1->next;
			x2 = x2->next;
		}
		else if (x2 == NULL) {
			r = x1->val + flag;
			x1 = x1->next;
		}
		else if (x1 == NULL) {
			r = x2->val + flag;
			x2 = x2->next;
		}

		if (r >= 10) {
			r -= 10;
			flag = 1;
		}
		else {
			flag = 0;
		}

		if (c == NULL) {
			c = new ListNode(r);
			n->next = c;
		}
		else {
			c->val = r;
		}
		n = c;
		c = c->next;
	}
	if (flag == 1) {
		c = new ListNode(1);
		n->next = c;
	}


	return s;
}

string longestPalindrome(string s) {
	int len = s.length();
	int maxplen = 1;
	int curlen, sp, ep;
	int i, j;

	if (len < 2) return s;
	sp = ep = 1;

	for (i = 0; i < len; i++) {
		curlen = 1;
		for (j = 1; i - j >= 0 && i + j < len; j++) {
			if (s.at(i - j) != s.at(i + j)) {
				break;
			}
			curlen += 2;
		}
		if (curlen > maxplen) {
			maxplen = curlen;
			sp = i - j + 1;
			ep = i + j - 1;
		}
	}

	for (i = 0; i < len - 1; i++) {
		if (s.at(i) == s.at(i + 1)) {
			curlen = 2;
			for (j = 1; i - j >= 0 && i + j + 1 < len; j++) {
				if (s.at(i - j) != s.at(i + j + 1)) {
					break;
				}
				curlen += 2;
			}
			if (curlen > maxplen) {
				maxplen = curlen;
				sp = i - j + 1;
				ep = i + j;
			}
		}
	} 

	return s.substr(sp, ep - sp + 1);
}

string convert(string s, int nRows) {
	if (nRows == 1) return s;

	string ns="";
	int len = s.length();
	char * arr = new char[len * nRows];
	int x, y, direction = 0;
	char c;
    
	memset(arr, 0, len*nRows);

	x = 0, y = 0;
	
	for (int i = 0; i < len; i++) {
		c = s.at(i);
		arr[y * len + x] = c;
		if (y == 0) {
			y++;
			direction = 1;
		}
		else if (y == nRows - 1) {
			x++;
			y--;
			direction = 2;
		}
		else if (direction == 1) {
			y++;
		}
		else if (direction == 2) {
			x++;
			y--;
		}
		else {
			//error
		}
	}

	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < len; j++) {
			if (arr[i * len + j] != 0x00) {
				ns += arr[i * len + j];
			}
		}
	}

	delete arr;
	return ns;
}

int reverse(int x) {
	int y, v;
	int minus = 0;
	
	if (x < 0) {
		minus = 1;
		x = -x;
	}

	y = 0;
	while (x != 0) {
		v = x % 10;
		x = x / 10;
		y *= 10;
		y += v;
	}

	if (minus) y = -y;
	return y;
}

int atoi_new(const char *str) {
    unsigned int r;
	int minus = 0;
	int status = 0;
	int i;

	i = 0;
	r = 0;
	do {
		if (status == 0 &&  isspace(str[i])) {
			i++;
		}
		else if (status == 0 && (str[i] == '+' || str[i] == '-')) {
			if (str[i] == '-') {
				minus = 1;
			}
			status = 1;
			i++;
		}
		else if ((status == 0 || status == 1 || status == 2) && isdigit(str[i])) {
			r *= 10;
			r += str[i] - '0';

			if (r > INT_MAX) {
				if (minus) return INT_MIN;
				else return INT_MAX;
			}
			i++;
			status = 2;
			if (r > INT_MAX / 10) status = 3;
		}
		else if (status == 3 && isdigit(str[i])) {
			if (minus) return INT_MIN;
			else return INT_MAX;
		}
		else {
			break;
		}
	} while (1);

	if (minus) return -(int)r;
	else return r;
}

bool isPalindrome(int x) {
    int j, k[20], times;
	if (x < 0) return false;

	j = x;
	times = 0;

	while (j > 0) {
		k[times] = j % 10;
		j /= 10;
		times ++;
	}

	j = x;
	for (int i = 0; i < times / 2; i++) {
		if (j % 10 != k[times - i - 1]) return false;
		j /= 10;
	}

	return true;
}

struct PosListNode {
	int machinepos;
	int stringpos;
	PosListNode *next;
	PosListNode(int x, int y) : machinepos(x), stringpos(y), next(NULL) {}
}; 

void deletePosList(struct PosListNode * sp) {
	PosListNode * p, *q;

	p = sp;
	while (p !=NULL) {
		q = p->next;
		delete p;
		p = q;
	}
}

bool isMatch(const char *s, const char *p) {
	int i, plen, j, statuspos, slen, machinelen;
	char *charname, *charcount, cc;
	PosListNode *start, *current, *tmp;
	
	start = current = NULL;

	plen = strlen(p);
	charname = new char[plen];
	charcount = new char[plen];
	memset(charname, 0, plen);
	memset(charcount, 0, plen);

	j = 0;
	for (i = 0; i < plen; i++) {
		if (isalpha(p[i]) || p[i] == '.') {
			charname[j] = p[i];
			j++;
		}
		else if (p[i] == '*') {
			charcount[j - 1] = '*';
		}
		else {
			//error
		}
	}
	machinelen = j;

	/* parser */
	slen = strlen(s);
	statuspos = 0;
	for (i = 0; i < slen; i++) {
OTHER_MATCH:
		cc = s[i];
		if (cc == charname[statuspos] || charname[statuspos] == '.') {
			if (charcount[statuspos] != '*') {
				statuspos++;
			}
			else if (cc = charname[statuspos + 1] || charname[statuspos + 1] == '.' || charcount[statuspos + 1] == '*') {
				if (current == NULL) {
					current = new PosListNode(statuspos + 1, i);
				}
				else {
					tmp = current;
					current = new PosListNode(statuspos + 1, i);
					tmp->next = current;
				}

				if (start == NULL) {
					start = current;
				}

			}
		}
		else if (charcount[statuspos] == '*') {
			statuspos ++;
			i--;
		}
		else {
			if (start != NULL) break;
			else return false;
		}
	}
	
	if (statuspos == machinelen) {
		deletePosList(start);
		return true;
	}
	if (statuspos == machinelen - 1 && charcount[statuspos] == '*') {
		deletePosList(start);
		return true;
	}
	if (start != NULL) {
		statuspos = start->machinepos;
		i = start->stringpos;
		tmp = start->next;
		delete start;
		start = tmp;
		if (start == NULL) current = start;

		goto OTHER_MATCH;
	}

	return false;        
}

#define FAIL		0x00
#define NEXT_NEXT	0x01
#define NEXT_MODE	0x02
#define NEXT_CHAR	0x04

int isCharMatch(char a, char b, char mode) {
	if (mode == '*') {
		if (b == '.' || a == b) {
			return NEXT_CHAR|NEXT_MODE|NEXT_NEXT;
		}
		else {
			return NEXT_MODE;
		}
	}
	else {
		if (a == b || b == '.') {
			return NEXT_NEXT;
		}
		else {
			return FAIL;
		}
	}
}

bool isIndexMatch(const char *s, const char *charname, const char*charcount, 
	int index_i, int index_j, int string_length, int mode_length) {
	int result;

	if (index_i == string_length && index_j == mode_length) return true;
	if (index_i < string_length && index_j < mode_length) {
		result = isCharMatch(s[index_i], charname[index_j], charcount[index_j]);
		switch (result) {
		case FAIL:
			return false;
		case NEXT_MODE:
			return isIndexMatch(s, charname, charcount, index_i, index_j + 1, string_length, mode_length);
		case NEXT_NEXT:
			return isIndexMatch(s, charname, charcount, index_i + 1, index_j + 1, string_length, mode_length);
		case NEXT_CHAR|NEXT_MODE|NEXT_NEXT:
			return isIndexMatch(s, charname, charcount, index_i, index_j + 1, string_length, mode_length) ||
				isIndexMatch(s, charname, charcount, index_i + 1, index_j, string_length, mode_length) ||
				isIndexMatch(s, charname, charcount, index_i + 1, index_j + 1, string_length, mode_length);
		default:
			return false;
		}
	}
	else if (index_i == string_length && index_j < mode_length) {
		for (int i = index_j; i < mode_length; i++) {
			if (charcount[i] != '*') return false;
		}
		return true;
	}		
	else return false;
}

bool isMatchNew(const char *s, const char *p) {
	int i, plen, j, slen, machinelen;
	char *charname, *charcount;

	plen = strlen(p);
	charname = new char[plen];
	charcount = new char[plen];
	memset(charname, 0, plen);
	memset(charcount, 0, plen);

	j = 0;
	for (i = 0; i < plen; i++) {
		if (isalpha(p[i]) || p[i] == '.') {
			charname[j] = p[i];
			j++;
		}
		else if (p[i] == '*') {
			charcount[j - 1] = '*';
		}
		else {
			//error
		}
	}
	machinelen = j;

	//merge 
	for (i = 0; i < machinelen - 1; i++) {
		if (charname[i] == charname [i + 1] && charcount[i] == '*' && charcount[i+1] == '*') {
			for (j = i + 2; j < machinelen; j++) {
				charname[j - 1] = charname[j];
				charcount[j - 1] = charcount[j];
			}
			machinelen--;
		}
	}

	slen = strlen(s);

	return isIndexMatch(s, charname, charcount, 0, 0, slen, machinelen);

}

struct HeightIndex {
	int h;
	int index;
	HeightIndex(int x, int y) : h(x), index(y) {}
};

bool orderHeight(const HeightIndex & x, const HeightIndex & y)
{
	return	x.h > y.h;
}

int maxArea(vector<int> &height) {
	int maxa = 0;
	int maxh = 0;
	unsigned int i;
	vector<HeightIndex> x;
	vector<HeightIndex> upv;
	vector<HeightIndex> downv;
	vector<HeightIndex>::iterator upit;
	vector<HeightIndex>::iterator downit;
	vector<HeightIndex>::iterator xit;

	for (i = 0; i < height.size(); i++) {
		x.push_back(HeightIndex(height.at(i), i));
	}
	
	std::sort(x.begin(), x.end(), orderHeight);
	
	xit = x.begin();

	upv.push_back(*xit);
	downv.push_back(*xit);

	int tmpi, tmph;
	for (i = 1; i < x.size(); i++) {
		tmpi = x.at(i).index;
		tmph = x.at(i).h;
		upit = upv.end();
		upit--;
		downit = downv.end();
		downit--;

		if (tmpi < upit->index) {
			if (upit->h == tmph) {
				upit->index = tmpi;
			}
			else {
				upv.push_back(x.at(i));
			}
		}
		else if (tmpi > downit->index) {
			if (downit->h == tmph) {
				downit->index = tmpi;
			}
			else {
				downv.push_back(x.at(i));
			}
		}
	}
	
	int k, l;
	while (upv.size() > 0 && downv.size() > 0) {
		k = min(upv.back().h, downv.back().h);
		l = downv.back().index - upv.back().index;

		if (maxa < k*l) maxa = k*l;
		
		if (upv.back().h > downv.back().h) {
			downv.pop_back();
		}
		else {
			upv.pop_back();
		}
	}

	return maxa;
}

string intToRoman(int num) {
	if (num > 3999 || num < 1) return "OVERFLOW";
	int a, b, c, d;
	string result = "";

	a = num % 10;
	b = num / 10 % 10;
	c = num / 100 % 10;
	d = num / 1000;

	switch (d) {
	case 0:
		break;
	case 3:
		result += "M";
	case 2:
		result += "M";
	case 1:
		result += "M";
		break;
	}

	switch (c) {
	case 0:
		break;
	case 3: result += "C";
	case 2: result += "C";
	case 1: result += "C";
		break;
	case 4: result += "CD";
		break;
	case 8: result += "DCCC"; break;
	case 7: result += "DCC"; break;
	case 6: result += "DC"; break;
	case 5: result += "D"; break;
	case 9: result += "CM"; break;
	}

	switch (b) {
	case 0:
		break;
	case 3: result += "X";
	case 2: result += "X";
	case 1: result += "X";
		break;
	case 4: result += "XL";
		break;
	case 8: result += "LXXX"; break;
	case 7: result += "LXX"; break;
	case 6: result += "LX"; break;
	case 5: result += "L"; break;
	case 9: result += "XC"; break;
	
	}

	switch (a) {
	case 0:
		break;
	case 3: result += "I";
	case 2: result += "I";
	case 1: result += "I";
		break;
	case 4: result += "IV";
		break;
	case 8: result += "VIII"; break;
	case 7: result += "VII"; break;
	case 6: result += "VI"; break;
	case 5: result += "V"; break;
	case 9: result += "IX"; break;
	
	}
	return result;
}

int romanToInt(string s) {
	unsigned int i;
	int result = 0;

	for (i = 0; i < s.length(); i++) {
		switch (s[i]) {
		case 'I':
			if (s[i + 1] == 'V') result -= 1;
			else if (s[i + 1] == 'X') result -= 1;
			else result += 1;
			break;
		case 'V':
			result += 5;
			break;
		case 'X':
			if (s[i + 1] == 'L') result -= 10;
			else if (s[i + 1] == 'C') result -= 10;
			else result += 10;
			break;
		case 'L':
			result += 50;
			break;
		case 'C':
			if (s[i + 1] == 'D') result -= 100;
			else if (s[i + 1] == 'M') result -= 100;
			else result += 100;
			break;
		case 'D':
			result += 500;
			break;
		case 'M':
			result += 1000;
			break;
		}
	}
	return result;
}

string longestCommonPrefix(vector<string> &strs) {
	if (strs.size() == 0) return "";
	if (strs.size() == 1) return strs.at(0);
	
	string maxs, mins, result;
	unsigned int i;
	result = "";
	maxs = strs.at(0);
	mins = strs.at(0);
	for (i = 1; i < strs.size(); i++) {
		if (maxs.compare(strs.at(i)) < 0) maxs = strs.at(i);
		else if(mins.compare(strs.at(i)) > 0) mins = strs.at(i);
	}

	i = 0;
	if (maxs.length() == 0 || mins.length() == 0) return "";
	do {
		if (i == maxs.length() || i == mins.length()) break;
		if (maxs[i] == mins[i]) {
			result += maxs[i];
			i++;
		}
		else break;
	} while (1);

    return result;
}

vector<vector<int> > threeSum(vector<int> &num) {
	vector<vector<int>> result;
	vector<int> sn(num);
	vector<int> pn, nn;

	vector<int> tmpvector;
	int zeroflag = 0;

	typedef pair <int, int> Int_Pair;
	typedef std::unordered_map<int, int> Intmap;

	Intmap pnmap;
	Intmap nnmap;
	unsigned int i, j, k;

	sort(sn.begin(), sn.end());

	j = 1; 
	k = 1;
	for (i = 0; i < sn.size(); i++) {
		if (sn.at(i) > 0 ) {
			pn.push_back(sn.at(i));
			pnmap.insert(Int_Pair(sn.at(i), j++));
		}
		else if (sn.at(i) < 0) {
			nn.push_back(sn.at(i));
			nnmap.insert(Int_Pair(sn.at(i), k++));
		}
		else {
			zeroflag++;
		}
	}

	if (zeroflag >= 3) {
		tmpvector.clear();
		tmpvector.push_back(0);
		tmpvector.push_back(0);
		tmpvector.push_back(0);
		result.push_back(tmpvector);
	}

	if (zeroflag) {
		int last = 0;
		for (i = 0; i < pn.size(); i++) {
			if (nnmap.find(-pn.at(i)) == nnmap.end()) {
				//not found
			}
			else {
				if (last == pn.at(i)) continue;
				last = pn.at(i);
				tmpvector.clear();
				tmpvector.push_back(-pn.at(i));
				tmpvector.push_back(0);
				tmpvector.push_back(pn.at(i));
				result.push_back(tmpvector);
			}
		}
	}
	int lasta, lastb;

	lasta = 0; lastb = 0;
	for (i = 0; i < pn.size(); i++) {
		if (i > 0) {
			if (pn.at(i) == pn.at(i - 1)) continue;
		}
		for (j = i + 1; j < pn.size(); j++) {
			if (nnmap.find(-pn.at(i) - pn.at(j)) == nnmap.end()) {
				//not found
			}
			else {
				if (lasta == pn.at(i) && lastb == pn.at(j)) continue;
				lasta = pn.at(i);
				lastb = pn.at(j);
				tmpvector.clear();
				tmpvector.push_back(-pn.at(i) - pn.at(j));
				tmpvector.push_back(pn.at(i));
				tmpvector.push_back(pn.at(j));
				result.push_back(tmpvector);
			}
		}
	}

	for (i = 0; i < nn.size(); i++) {
		if (i > 0) {
			if (nn.at(i) == nn.at(i - 1)) continue;
		}
		for (j = i + 1; j < nn.size(); j++) {
			if (pnmap.find(-nn.at(i) - nn.at(j)) == pnmap.end()) {
				//not found
			}
			else {
				if (lasta == nn.at(i) && lastb == nn.at(j)) continue;
				lasta = nn.at(i);
				lastb = nn.at(j);
				tmpvector.clear();
				tmpvector.push_back(nn.at(i));
				tmpvector.push_back(nn.at(j));
				tmpvector.push_back(-nn.at(i) - nn.at(j));
				result.push_back(tmpvector);
			}
		}
	}

	return result;    
}

struct ValueIndex {
	int v;
	int index1;
	int index2;
	ValueIndex(int x, int y, int z) : v(x), index1(y), index2(z) {}
};

bool orderValue(const ValueIndex & x, const ValueIndex & y)
{
	return	x.v > y.v;
}

int threeSumClosest(vector<int> &num, int target) {
	vector<ValueIndex> vlist;
	int i, j, gap = INT_MAX, result, count;

	if (num.size() == 3) return num.at(0) + num.at(1) + num.at(2);
    
	sort(num.begin(), num.end());

	count = 1;
	for (i = 0; i < num.size(); i++) {
		if (i > 0) {
			if (num.at(i) == num.at(i - 1)) count++;
			else count = 1;
		}
		if (count == 3) {
			if (num.at(i) * 3 < gap) result = num.at(i) * 3;
			continue;
		}
		if (count > 3) continue;

		vlist.push_back(ValueIndex(target - num.at(i), -1, i));
	}

	if (vlist.size() < 3) return result;
	if (vlist.size() == 3) {
		int tmp = 3 * target - vlist.at(0).v - vlist.at(1).v - vlist.at(2).v;
		if (abs(target - tmp) < abs(target - result)) return tmp;
		return result;
	}
	for (i = 0; i < num.size(); i++) {
		for (j = i + 1; j < num.size(); j++) {
			vlist.push_back(ValueIndex(num.at(i) + num.at(j), i, j));
		}
	}

	sort(vlist.begin(), vlist.end(), orderValue);

	for (i = 0; i < vlist.size() - 1; i++) {
		if (vlist.at(i).index1 == -1) {
			for (j = i - 1; j >= 0; j--) {	/*注意此处不能用unsigned int, i - 1会溢出*/
				if (vlist.at(j).v - vlist.at(i).v > gap) break;
				if (vlist.at(j).index1 >= 0) {
					if (vlist.at(j).index1 != vlist.at(i).index2 && 
						vlist.at(j).index2 != vlist.at(i).index2) {
						if (vlist.at(j).v - vlist.at(i).v < gap) {
							gap = vlist.at(j).v - vlist.at(i).v;
							if (gap == 0) return target;
							result = target + gap;
							break;
						}
					}
				}
			}
			
			for (j = i + 1; j < vlist.size(); j++) {
				if (vlist.at(i).v - vlist.at(j).v > gap) break;
				if (vlist.at(j).index1 >= 0) {
					if (vlist.at(j).index1 != vlist.at(i).index2 && 
						vlist.at(j).index2 != vlist.at(i).index2) {
						if (vlist.at(i).v - vlist.at(j).v < gap) {
							gap = vlist.at(i).v - vlist.at(j).v;
							if (gap == 0) return target;
							result = target - gap;
							break;
						}
					}
				}
			}
		}
	}

	return result;
}

bool orderVector(const vector<int> & x, const vector<int> & y)
{
	if (x.size() == 0 || y.size() == 0) return false;

	if (x.at(0) > y.at(0)) return true;
	else if (x.at(0) < y.at(0)) return false;
	else if (x.at(1) > y.at(1)) return true;
	else if (x.at(1) < y.at(1)) return false;
	else if (x.at(2) > y.at(2)) return true;
	else if (x.at(2) < y.at(2)) return false;
	return false;
}
bool compareVector(const vector<int> & x, const vector<int> & y)
{
	if (x.at(0) == y.at(0) && x.at(1) == y.at(1) && x.at(2) == y.at(2)) return true;
	else return false;
}
bool checkInsert(ValueIndex &x, ValueIndex &y, vector<vector<int>> &result, vector<int> &num)
{
	vector<int> m;
	if (x.index1 != y.index1 &&
		x.index2 != y.index1 &&
		x.index1 != y.index2 &&
		x.index2 != y.index2) {
		m.clear();
		m.push_back(x.index1);
		m.push_back(x.index2);
		m.push_back(y.index1);
		m.push_back(y.index2);
		sort(m.begin(),m.end());
		for (int n = 0; n < m.size(); n++)
			m.at(n) = num.at(m.at(n));

		result.push_back(m);
		return true;
	}
	return false;
}
vector<vector<int> > fourSum(vector<int> &num, int target) {
	vector<vector<int> > result;
	vector<vector<int> > pureresult;
	vector<int> x;
	vector<ValueIndex> va;
	int i, j;

	if (num.size() < 4) return result;

	sort(num.begin(), num.end());

	for (i = 0; i < num.size(); i++) {
		for (j = i + 1; j < num.size(); j++) {
			va.push_back(ValueIndex(num.at(i) + num.at(j), i, j));
		}
	}
	sort(va.begin(), va.end(), orderValue);

	vector<ValueIndex> vb(va);

	i = 0; j = vb.size() - 1;
	int k;
	do {
		if (va.at(i).v + vb.at(j).v == target) {
			checkInsert(va.at(i), vb.at(j), result, num);
			for (k = 1; i + k <va.size(); k++ ) {
				if (va.at(i + k).v + vb.at(j).v != target) break;
				else {
					checkInsert(va.at(i + k), vb.at(j), result, num);
				}
			} 
			
			for (k = 1; j - k >= 0; k++ ) {
				if (va.at(i).v + vb.at(j - k).v != target) break;
				else {
					checkInsert(va.at(i), vb.at(j - k), result, num);					
				}
			}

			if (i < va.size() - 1 && j > 0) {
				i++;
				j--;
			}
			else if (i < va.size() - 1 && j == 0) i++;
			else if (i == va.size() - 1 && j > 0) j--;
			else break;
		}
		else if (va.at(i).v + vb.at(j).v > target) { //greater
			i++;
			if (i == va.size()) break;
		}
		else {	//less
			j--;
			if (j < 0) break;
		}
		
	} while (1);

	sort(result.begin(), result.end(), orderVector);
	if (result.size() > 0) pureresult.push_back(result.at(0));
	for (i = 1; i < result.size(); i++) {
		if (compareVector(result.at(i), result.at(i - 1))) continue;
		pureresult.push_back(result.at(i));
	}

	return pureresult;
}
vector<string> letterCombinations(string digits) {
    vector<string> result;
	string x, base;
	unsigned int i, j;

	if (digits.size() == 0) {
		result.push_back("");
		return result;
	}
	else if (digits.size() == 1) {
		switch (digits.at(0) - '0') {
		case 2:
			result.push_back("a");
			result.push_back("b");
			result.push_back("c");
			break;
		case 3:
			result.push_back("d");
			result.push_back("e");
			result.push_back("f");
			break;
		case 4:
			result.push_back("g");
			result.push_back("h");
			result.push_back("i");
			break;
		case 5:
			result.push_back("j");
			result.push_back("k");
			result.push_back("l");
			break;
		case 6:
			result.push_back("m");
			result.push_back("n");
			result.push_back("o");
			break;
		case 7:
			result.push_back("p");
			result.push_back("q");
			result.push_back("r");
			result.push_back("s");
			break;
		case 8:
			result.push_back("t");
			result.push_back("u");
			result.push_back("v");
			break;
		case 9:
			result.push_back("w");
			result.push_back("x");
			result.push_back("y");
			result.push_back("z");
			break;
		default:	break;
		}
		return result;
	}
	else {
		x = digits.substr(digits.length() - 1, 1);
		base = digits.substr(0, digits.length() - 1);

		vector<string> bs = letterCombinations(base);
		vector<string> xs = letterCombinations(x);
		string tmp;
		for (i = 0; i < bs.size(); i++) {
			for (j = 0; j < xs.size(); j++) {
				tmp = "";
				tmp.append(bs.at(i));
				tmp.append(xs.at(j));
				result.push_back(tmp);
			}
		}
	}

    return result;
}
ListNode *removeNthFromEnd(ListNode *head, int n) { //O(t + n)
	ListNode *p, *q, *prev;
	int i;

	if (head == NULL) return NULL;
	if (head->next == NULL) {
		delete head;
		return NULL;
	}
	p = head;
	i = 0;
	
	while (p != NULL) {
		p = p->next;
		i++;
		if (i == n) {
			q = head;
		}
		if (i > n) {
			prev = q;
			q = q->next;
		}
	}
	if (q == head) {
		head = head->next;
		delete q;
		return head;
	}
	else {
		prev->next = q->next;
		delete q;
		return head;
	}
}
bool isValid(string s) {
	string xx;
	unsigned int i;

	for (i = 0; i < s.length(); i++) {
		switch (s.at(i)) {
		case '(':	
			xx.push_back('('); 
			break;
		case ')':	
			if (xx.back() != '(') 
				return false;
			xx.pop_back();
			break;
		case '[':	
			xx.push_back('['); 
			break;
		case ']':	
			if (xx.back() != '[') 
				return false;
			xx.pop_back();
			break;
		case '{':	
			xx.push_back('{'); 
			break;
		case '}':	
			if (xx.back() != '{') 
				return false;
			xx.pop_back();
			break;
		}
	}

	if (xx.length() > 0) return false;

	return true;
}

void generateParenthesis(string now, int push_count, int pop_count, 
	int limit, vector<string> &rr)
{
	string tmpstr;

	if (pop_count == limit) {
		rr.push_back(now);
		return;
	}

	if (push_count > pop_count) {
		tmpstr = now;
		tmpstr.append(")");
		generateParenthesis(tmpstr, push_count, pop_count + 1, limit, rr);
	}

	if (push_count < limit) {
		tmpstr = now;
		tmpstr.append("(");
		generateParenthesis(tmpstr, push_count + 1, pop_count, limit, rr);
	}

}
vector<string> generateParenthesis(int n) {
	vector<string> result;
	string tmp = "";

	generateParenthesis(tmp, 0, 0, n, result);
	return result;
}
ListNode *merge2Lists(ListNode * list1, ListNode * list2) {
	ListNode *p, *q, *head, *current;

	p = list1;
	q = list2;

	if (p == NULL) return q;
	if (q == NULL) return p;

	if (p->val < q->val) {
		head = p;
		p = p->next;
	}
	else {
		head = q;
		q = q->next;
	}
	current = head;

	while (p != NULL && q != NULL) {
		if (p->val < q->val) {
			current->next = p;
			current = current->next;
			p = p->next;
		}
		else {
			current->next = q;
			current = current->next;
			q = q->next;
		}
	}

	if (p == NULL) {
		current->next = q;
	}
	else {
		current->next = p;
	}

	return head;
}

ListNode *mergeKLists(vector<ListNode *> &lists) {
	unsigned int i;

	if (lists.size() == 0) return NULL;

	ListNode * tmp = lists.at(0);
	for (i = 1; i < lists.size(); i++) {
		tmp = merge2Lists(tmp, lists.at(i));
	}
	return tmp;
}

ListNode *swapPairs(ListNode *head) {
	ListNode *p, *q, *prev, *nhead;
	if (head == NULL || head->next == NULL) return head;

	p = head;
	q = head->next;
	prev = NULL;

	nhead = q;
	p->next = q->next;
	q->next = p;
	prev = p;

	p = p->next;
	if (p == NULL) return nhead;
	q = p->next;
		
	while (p != NULL && q != NULL) {
		p->next = q->next;	//swap, post link
		q->next = p;		//swap
		prev->next = q;		//prev link
		prev = p;
		p = p->next;
		if (p == NULL) break;
		q = p->next;
	}

	return nhead;
}

int _tmain(int argc, _TCHAR* argv[])
{
	
	
	/* for letterCombinations
	letterCombinations("234");
	*/

	/* for 4sum
	vector <int> t;
	vector<int>::iterator it;

	it = t.begin();
	//0,-6,5,8,-8,7,0,-4,1,8,-2,3,-1,-4,-6,8,3
	it = t.insert(it, -4);
	it = t.insert(it, -3);
	it = t.insert(it, -2);
	it = t.insert(it, -1);
	it = t.insert(it, 0);
	it = t.insert(it, 0);
	it = t.insert(it, 1);
	it = t.insert(it, 2);
	
	it = t.insert(it, 3);
	it = t.insert(it, 4);
	fourSum(t, 0);
	*/

	/* for 3SumClosest
	vector <int> t;
	vector<int>::iterator it;

	it = t.begin();
	it = t.insert(it, -1);
	it = t.insert(it, 2);
	it = t.insert(it, 1);
	it = t.insert(it, -4);
	threeSumClosest(t, 1);
	*/

	/* for 3Sum
	vector <int> t;
	vector<int>::iterator it;

	it = t.begin();
	it = t.insert(it, 13);
	it = t.insert(it, -33);
	it = t.insert(it, 92);
	it = t.insert(it, 20);
	it = t.insert(it, 0);
	it = t.insert(it, -20);
	threeSum(t);
	*/
	/* for maxArea
	vector<int> t;
	vector<int>::iterator it;

	it = t.begin();
	it = t.insert(it, 13);
	it = t.insert(it, 33);
	it = t.insert(it, 92);
	it = t.insert(it, 16);
	it = t.insert(it, 37);
	it = t.insert(it, 28);
	cout<<' '<<maxArea(t);
	*/

	/* for Regular Expression
	cout<<' '<<isMatchNew("aaaaaaaaaaaaab", "a*a*a*a*a*a*a*a*a*a*c");
	*/

	/* for is Palindrome integer
	cout<<' '<<isPalindrome(12321);
	*/
	/* for zigzag convert
	cout<<' '<<convert("PAYPALISHIRING", 3).data();
	*/
	/* for lengthOfLongestSubstring
	int l = lengthOfLongestSubstring("adfhrjadhfe");
	cout<<' '<<l;
	*/
	;
	/* for findMedianSortedArrays
	int X[2] = {1,2};
	int Y[3] = {1,2,3};
	;
	double r = findMedianSortedArrays(X, 2, Y, 3);
	cout<< ' '<<r;
	*/
	;
	/* for twoSum
	vector<int> t;
	vector<int>::iterator it;

	it = t.begin();
	it = t.insert(it, 5);
	it = t.insert(it, 75);
	it = t.insert(it, 25);

	vector<int> x = twoSum(t, 100);

	for (unsigned int j = 0; j < x.size(); j++) {
		cout<<' '<<x.at(j);
	}
	*/
	return 0;
}
