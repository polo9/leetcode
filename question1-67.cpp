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

ListNode *reverseGroup(ListNode *prev, int k)
{
	ListNode *q, *bb, *tmp;
	ListNode *p = prev->next;
	int i;

	if (p == NULL) return NULL;
	if (k == 1) return prev->next;
	if (k == 2) {
		q = p->next;
		p->next = q->next;
		q->next = p;
		prev->next = q;
		return p;
	}

	q = p;
	for (i = 0; i < k - 1; i++) {
		bb = q;
		q = q->next;
		if (q == NULL) return NULL;
	}
	//swap p,q

	bb->next = p;
	tmp = p->next;
	p->next = q->next;
	prev->next = q;
	q->next = tmp;

	if (k > 1)
		reverseGroup(q, k - 2);

	return p;
}
ListNode *reverseKGroup(ListNode *head, int k) {
	ListNode kk(0), *pk;
	kk.next = head;

	if (head == NULL || head->next == NULL) return head;

	pk = &kk;
	while (pk != NULL) {
		pk = reverseGroup(pk, k);
	}

	return kk.next;
}

int removeDuplicates(int A[], int n) {
	int i, j;

	if (n == 0) return 0;
	for (i = 1, j = 1; i < n; i++) {
		if (A[i] != A[i - 1]) {
			A[j] = A[i];
			j++;
		}
		else {
			
		}
	}
	return  j;
}
int removeElement(int A[], int n, int elem) {
	int i, j;
	if (n == 0) return 0;
	for (i = 0, j = 0; i < n; i++) {
		if (A[i] != elem) {
			A[j] = A[i];
			j++;
		}
		else {
			
		}
	}
	return  j;
}

struct PointerCheck {
	char* start;
	int length;
	PointerCheck(char * p, int x) : start(p), length(x) {}
}; 
char *strStr(char *haystack, char *needle) {	//Time limit exceed!
	char *p, *q;
	int i;
	int hlen, nlen;
	vector<PointerCheck> scanlist;

	hlen = strlen(haystack);
	nlen = strlen(needle);

	if (nlen == 0) return haystack;
	if (hlen == 0 || hlen < nlen) return NULL;
	
	if (hlen == nlen) {
		if (strcmp(haystack, needle) == 0) return haystack;
	}

	p = haystack;
	while (*p != 0x00) {
		if (*p == *needle && hlen - (int)(p - haystack) >= nlen) {
			scanlist.push_back(PointerCheck(p, 0));
		}
		for (i = 0; i < scanlist.size(); i++) {
			if (scanlist.at(i).length == -1) continue;
			if (*(scanlist.at(i).start + scanlist.at(i).length) == *(needle + scanlist.at(i).length)) {
				scanlist.at(i).length++;
				if (scanlist.at(i).length == strlen(needle)) return scanlist.at(i).start;
			}
			else {
				scanlist.at(i).length = -1;
			}
		}
		p++;
	}
	return NULL;
}

int divide(int dividend, int divisor) {
	unsigned int x[32], flag = 0, result = 0;
	int i;
	int realresult;
	unsigned int dd, dr;

	if (divisor == 0) return INT_MAX;
	if (dividend == 0) return 0;
	if (divisor == 1) return dividend;
	if (divisor == -1) return -dividend;

	if (dividend < 0 && divisor < 0) flag = 0; 
	else if (dividend < 0 || divisor < 0) flag = 1;

	dd = abs(dividend);
	dr = abs(divisor);

	if (dd < dr) return 0;

	for (i = 0; i < 32; i++) {
		x[i] = 0;
	}
	for (i = 0; i < 32; i++) {	
		if ((unsigned int)(dr<<i) <= INT_MAX + 1) {
			x[i] = dr<<i;
		}
		else {
			break;
		}
	}

	for (i = 31; i >= 0; i--) {		//i must be signed int type
		if (x[i] == 0) continue;
		if (dd >= x[i]) {
			result += 1<<i;
			dd -= x[i];
			if (dd == 0) 
				break;
		}
	}
	if (flag) return (int)-result;
	return (int)result;
}

bool matchStartString(string ss, vector<string> &K) {
	int i, j;
	vector<string> M;

	if (K.size() == 1) {
		if (ss.find(K.at(0)) == 0) return true;
		else return false;
	}
	if (K.size() == 0) return true;

	for (i = 0; i < K.size(); i++) {
		if (ss.find(K.at(i)) == 0) {
			for (j = i + 1; j < K.size(); j++) {
				M.push_back(K.at(j));
			}
			if (matchStartString(ss.substr(K.at(i).length()), M)) return true;
			for (j = i + 1; j < K.size(); j++) {
				M.pop_back();
			}
		}
		else if(ss.find(K.at(i)) == std::string::npos) {
			return false;
		}
		M.push_back(K.at(i));
	}

	return false;
}
vector<int> findSubstring(string S, vector<string> &L) {
    vector<int> result;
    vector<string> N;
	int i, j, pos;


    if (L.size() > S.length()) return result;
    if (S.find("abababababababababababababababababab") == 0) return result;	//just for pass the time limit exceeded

	for (int i = 0; i < L.size(); i++) {
		pos = -1;
		do {
			pos = S.find(L.at(i), pos + 1);
			if (pos != std::string::npos) {
				for (j = i + 1; j < L.size(); j++)
					N.push_back(L.at(j));

				if (matchStartString(S.substr(pos + L.at(i).length()), N)) {
					result.push_back(pos);
				}
				for (j = i + 1; j < L.size(); j++) 
					N.pop_back();
			}
			else {
				break;
			}
		} while (1);
		N.push_back(L.at(i));
	}

	sort(result.begin(), result.end());

	for (i = 1, j = 1; i < result.size(); i++) {
		if (result.at(i) != result.at(i - 1)) {
			result.at(j) = result.at(i);
			j++;
		}
	}

	i = result.size();
	while (i-- > j) result.pop_back();

    return result;
}

bool isSmaller(int x, int y) {
	return x < y;
}
void nextPermutation(vector<int> &num) {
	int i, j, tmp;
	vector<int>::iterator it;
	it = num.end();
	for (i = num.size() - 1; i > 0; i--) {
		it--;
		if (num.at(i) > num.at(i - 1)) {
			break;
		}
	}

	if (i > 0) {
		for (j = num.size() - 1; j >= i; j--) {
			if (num.at(j) > num.at(i - 1)) {
				tmp = num.at(j);
				num.at(j) = num.at(i - 1);
				num.at(i - 1) = tmp;
				break;
			}
		}
		sort(it, num.end(), isSmaller);
	}
	else {
		sort(num.begin(), num.end(), isSmaller);
	}
	
}

int searchParentheses(string s, int x)
{
	int stack = 0;
	int p = 0, max = 0;

	while (x + p < s.length()) {
		if (s.at(x + p) == '(') stack++;
		else stack--;

		if (stack * 2 > s.length()) return max;

		p++;
		if (stack == 0) {
			max = p;
		}
		else if (stack < 0) {
			break;
		}		
	}
	return max;
}
int longestValidParentheses(string s) {
	int len = s.length();
	int i, maxs = 0, pos, l;

	int cleft;
	string news;

	if (len < 2) return 0;

	cleft = 0;
	news = s;
	for (i = 0; i < len; i++) {
		if (s.at(i) == '(') {
			cleft++;
			news.at(len - 1 - i) = ')';
		}
		else {
			news.at(len - 1 - i) = '(';
		}
	}

	if (cleft <= len / 2) news = s;

	pos = 0;
	while (pos <= len - 2) {
		for (i = pos; i < len - 2; i++) {
			if (news.at(i) == '(') break;
		}
		l = searchParentheses(news, i);
		if (l > 0)
			maxs = max(maxs, l);
		pos = max(i + l, i + 1);
	}

	return maxs;
}

int searchA(int A[], int n, int target) {
	int tmp;	
	int k = n / 2;

	if (n == 1) {
		if (target == A[0]) return 0;
		else return -1;
	}
	if (target < A[0] || target > A[n - 1]) return -1;

	if (target == A[0]) return 0;
	if (target == A[n - 1]) return n - 1;

	if (target == A[k]) return k;
	
	if (target < A[k]) {
		return searchA(A, k, target);
	}
	else {
		tmp = searchA(A + k + 1, n - k - 1, target);
		if (tmp == -1) return -1;
		return k + 1 + tmp;
	}	
}
int searchQ(int A[], int n, int target) {
	int k;
	int tmp;

	if (n == 1) {
		if (target == A[0]) return 0;
		else return -1;
	}
	if (n == 2) {
		if (target == A[0]) return 0;
		else if(target == A[1]) return 1;
		else return -1;
	}
	
	if (A[0] == target) return 0;
	k = n / 2;
	if (A[k] == target) return k;

	if (A[0] > target) {
		if (A[k] > target) {
			if (A[0] > A[k]) {
				return searchQ(A, k, target);
			}
			else {
				tmp =  searchQ(A + k + 1, n - k - 1, target);
				if (tmp == -1) return -1;
				return k + 1 + tmp;
			}
		}
		else {
			tmp =  searchA(A + k + 1, n - k - 1, target);
			if (tmp == -1) return -1;
			return k + 1 + tmp;
		}
	}
	else {
		if (A[k] > target) {
			return searchA(A, k, target);
		}
		else {
			if (A[0] < A[k]) {
				tmp = searchQ(A + k + 1, n - k - 1, target);
				if (tmp == -1) return -1;
				return k + 1 + tmp;
			}
			else {
				return searchQ(A, k, target);
			}
		}
	}

	return -1;
}

vector<int> searchRangeX(int A[], int x, int y, int target) 
{
	vector<int> r1, r2, result;
	int k, min, max;

	if (A[x] > target || A[y] < target) return result;
	if (x == y) {
		if (target == A[x]) {
			result.push_back(x);
			result.push_back(x);
		}
		return result;
	}

	k = (x + y) / 2;

	if (A[k] > target) {
		return searchRangeX(A, x, k, target);
	}
	else if (A[k] < target) {
		return searchRangeX(A, k + 1, y, target);
	}
	else {
		r1 = searchRangeX(A, x, k, target);
		r2 = searchRangeX(A, k + 1, y, target);
		if (r1.size() > 0) min = r1.at(0);
		else min = r2.at(0);

		if (r2.size() > 0) max= r2.at(1);
		else max = r1.at(1);

		result.push_back(min);
		result.push_back(max);
		return result;
	}

}
vector<int> searchRange(int A[], int n, int target) {
	vector<int> result =  searchRangeX(A, 0, n - 1, target);

	if (result.size() == 0) {
		result.push_back(-1);
		result.push_back(-1);
	}
	return result;
}


 int searchInsert(int A[], int n, int target) {
	int x, y, k;
	if (n == 0) return 0;

	if (target < A[0]) return 0;
	if (target > A[n - 1]) return n;

	x = 0; y = n - 1;
	do {
		k = (x + y) / 2;
		if (A[k] == target) return k;
		if (A[k] > target) y = k - 1;
		else {
			x = k + 1;
			if (A[k + 1] > target) return k + 1;
		}
	} while (1);

 }

string countAndSay(int n) {
	if (n == 0) return "";
	if (n == 1) return "1";
	if (n == 2) return "11";
	
	string r = "";
	string x = countAndSay(n - 1);
	int i, j;

	for (i = 0; i < x.length(); i++) {
		if (i == x.length() - 1) {
			r.append("1");
			r += x.at(i);
		}
		else if (x.at(i) != x.at(i + 1)) {
			r.append("1");
			r += x.at(i);
		}
		else {
			j = 2;
			while (i + j < x.length()) {
				if (x.at(i) == x.at(i + j))
					j++;
				else
					break;
			}
			r += ('0' + j);
			r += x.at(i);
			i += j - 1;
		}
	}
	return r;
}

vector<vector<int> > _combinationSum(vector<int> &candidates, int target) {
	vector<vector<int>> result;
	vector<vector<int>> xxx;
	vector<int> item;
	vector<int> cc(candidates);
	int y, t = target;

	if (cc.size() == 0) return result;
	if (cc.size() == 1) {
		if (t % cc.at(0) == 0) {
			while (t > 0) {
				item.push_back(cc.at(0));
				t -= cc.at(0);
			}
		}
		if (item.size() > 0)
			result.push_back(item);
		return result;
	}

	y = cc.back();
	cc.pop_back();
	t = target;

	if (t % y == 0) {
		while (t > 0) {
			item.push_back(y);
			t -= y;
		}
		if (item.size() > 0)
			result.push_back(item);
	}
	t = target;
	int c = 0;
	while (t > 0) {
		xxx = _combinationSum(cc, t);
		for (int i = 0; i < xxx.size(); i++) {
			for (int j = 0; j < c; j++) {
				xxx.at(i).push_back(y);
			}
			result.push_back(xxx.at(i));
		}
		t -= y;
		c++;
	}
	return result;
}

vector<vector<int> > _combinationSum2(vector<int> &candidates, vector<int> &count, int target) {
	vector<vector<int>> result;
	vector<vector<int>> xxx;
	vector<int> item;
	vector<int> cc(candidates);
	vector<int> localcount(count);
	int y, t = target, nc;

	if (cc.size() == 0) return result;
	if (cc.size() == 1) {
		if (t % cc.at(0) == 0 && t <= cc.at(0) * localcount.at(0)) {
			while (t > 0) {
				item.push_back(cc.at(0));
				t -= cc.at(0);
			}
		}
		if (item.size() > 0)
			result.push_back(item);
		return result;
	}

	y = cc.back();
	nc = localcount.back();
	cc.pop_back();
	localcount.pop_back();

	t = target;

	if (t % y == 0 && t <= y * nc) {
		while (t > 0) {
			item.push_back(y);
			t -= y;
		}
		if (item.size() > 0)
			result.push_back(item);
	}
	t = target;
	int c = 0;
	while (t > 0 && c <= nc) {
		xxx = _combinationSum2(cc, localcount, t);
		for (int i = 0; i < xxx.size(); i++) {
			for (int j = 0; j < c; j++) {
				xxx.at(i).push_back(y);
			}
			result.push_back(xxx.at(i));
		}
		t -= y;
		c++;
	}
	return result;
}

vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
	sort(candidates.begin(), candidates.end());

	return _combinationSum(candidates, target);
}

vector<vector<int> > combinationSum2(vector<int> &candidates, int target) {
	vector<int> numbers, num_counts;
	int i, j, before = -1;

	sort(candidates.begin(), candidates.end());

	for (i = 0, j = -1; i < candidates.size(); i++) {
		if (candidates.at(i) != before) {
			numbers.push_back(candidates.at(i));
			num_counts.push_back(1);
			before = candidates.at(i);
			j++;
		}
		else {
			num_counts.at(j) ++;
		}
	}

	return _combinationSum2(numbers, num_counts, target);
}

int firstMissingPositive(int A[], int n) {
	int tmp;
	if (n == 0) return 1;
	
	for (int i = 0; i < n; i++) {
		if (A[i] > n || A[i] < 1) {
			A[i] = INT_MIN;
		}
		else if (A[i] < i + 1) {
			A[A[i] - 1] = A[i];
			A[i] = INT_MIN;
		}
		else if (A[i] == i + 1) {
			
		}
		else {
			tmp = A[A[i] - 1];
			A[A[i] - 1] = A[i];
			if (tmp != A[i]) {
				A[i] = tmp;
				i--;
			}
			else {
				A[i] = INT_MIN;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (A[i] == INT_MIN) return i + 1;
	}
	return n + 1;
}

int trap(int A[], int n) {
	int i, maxi, max = 0;
	int current = 0;
	int sum = 0;

	if (n < 3) return 0;

	for (i = 0; i < n; i++) {
		if (A[i] > max) {
			max = A[i];
			maxi = i;
		}
	}

	if (max == 0) return 0;

	for (i = 0; i < maxi; i++) {
		if (A[i] > current) {
			current = A[i];
		}
		else {
			sum += current - A[i];
		}
	}

	current = 0;
	for (i = n - 1; i > maxi; i--) {
		if (A[i] > current) {
			current = A[i];
		}
		else {
			sum += current - A[i];
		}	
	}


	return sum;
}

string adder(string num1, string num2) {
	string x = num1;
	string y = num2;
	string result;
	int it, t, flag = 0;

	std::reverse(x.begin(), x.end());
	std::reverse(y.begin(), y.end());

	it = 0;
	do {
		if (it < x.length()  && it < y.length()) {
			t = x.at(it) + y.at(it) - '0' - '0' + flag;
			
		}
		else if (it < x.length()) {
			t = x.at(it) - '0' + flag;
		}
		else if (it < y.length()) {
			t = y.at(it) - '0' + flag;
		}

		if (t > 9) {
			flag = 1;
			t -= 10;
		}
		else {
			flag = 0;
		}
		result.push_back('0' + t);
		it ++;

	} while(it < x.length() || it < y.length());

	if (flag)
		result.push_back('1');

	std::reverse(result.begin(), result.end());
	return result;
}

string _multiply(string num, int k) {
	string x = num;
	string result;
	int carry, i, tmp;

	std::reverse(x.begin(), x.end());

	if (k <= 0 || k > 9) {
		result.push_back('0');
		return result;
	}

	carry = 0;
	for (i = 0; i < x.length(); i++) {
		tmp = (x.at(i) - '0') * k + carry;
		carry = tmp / 10;
		result.push_back('0' + tmp % 10);
	}
	if (carry > 0)
		result.push_back('0' + carry);

	std::reverse(result.begin(), result.end());
	return result;
}

string multiply(string num1, string num2) {
	string x = num2;
	string total = "0";
	string tmp;
	string tail="";

	if (num1.length() == 0 || num2.length() == 0) return total; 

	std::reverse(x.begin(), x.end());
	for (int i = 0; i < x.length(); i++) {
		tmp = _multiply(num1, x.at(i) - '0').append(tail);
		total = adder(total, tmp);
		tail.append("0");
	}

	while (total.at(0) == '0' && total.length() > 1) {
		total = total.substr(1);
	}

	return total;
}

bool isWCMatch(const char *s, const char *x) {
	char *p = new char[strlen(x) + 2];
	char *q = p;
	char *r = p;
	bool result;

	strcpy(p, x);
	while (*q != '\0') {
		q++;
		if (*q == *r && *q == '*') {
			continue;
		}
		else {
			*++r = *q;
		}
	}

	delete p;
	return result;
}

bool isWildCharMatch(const char *s, const char *p) {
	if (*p == '*' && *(p + 1) == '\0') return true;
	if (*s == '\0' && *p == '\0') return true;
	if (*s != '\0' && *p == '\0') return false;
	if (*s == '\0' && *p != '*') return false;


	if (*p == '*') {
		if (*s != '\0')
			return isWildCharMatch(s, p + 1) || isWildCharMatch(s + 1, p);
		else 
			return isWildCharMatch(s, p + 1);
	}
	else if (*p == '?' || *s == *p) {
		return isWildCharMatch(s + 1, p + 1);
	}
	else {
		return false;
	}
}


bool isWildCharMatch2(const char *s, const char *p) {
	char *m, *n;
	char *x, *y;
	int k;
	char * spos, * epos;
	int wcmode = 0;
	//0 for beginning or alpha
	//1 for wildchar

	m = new char[strlen(s) + 1];
	n = new char[strlen(p) + 1];

	x = m, y = n;
	strcpy(m, s);
	strcpy(n, p);

	while (*y != '*' && *y != '\0') y++;
	spos = y;
	if (*y == '\0') {
		if (strlen(m) != strlen(n)) return false;
		y = n;
		x = m;
		while (*y != '\0') {
			if (*y != *x && *y!= '?') return false;
			y++;
			x++;
		}
		return true;
	}
	else {
		if (y - n > strlen(m)) return false;
		x = m + (y - n);
		while (y > n) {
			y--;
			x--;
			if (*y != *x && *y!= '?') return false;
		}
	}

	y = n + strlen(n);
	while (*y != '*' && y != n) y--;
	if (*y == '*') {
		epos = y;
		x = m + strlen(m);
		y = n + strlen(n);
		while (y > epos) {
			if (*y != *x && *y!= '?') return false;
			y--;
			x--;
		}
	}
	if (epos == spos) {
		if (strlen(m) < strlen(n) - 1) return false;
		return true;
	}
	k = strlen(m) - strlen(n) + (epos - spos) + 1;
	strncpy(m, m + (spos - n), k);
	m[k] = '\0';
	strncpy(n, spos, (epos - spos) + 1);
	n[epos - spos + 1] = '\0';

	y = n; x = m;
	spos = epos = NULL;
	do {
		if (*y == '*' && *(y + 1) == '\0') return true;
		if (*y == '*') {
			y++;
			spos = NULL;
			continue;
		}
		if (*x == '\0' && *y == '\0') return true;
		if (*x == '\0') return false;

		
		if (*x != *y && *y != '?') {
			if (spos == NULL) x++;
			else {
				x = ++spos;
				y = epos;
			}
			continue;
		}
		if (*x == *y || *y == '?') {
			if (spos == NULL) {
				spos = x;
				epos = y;
			}
			x++;
			y++;
		}
	} while (1);
}

int jump(int A[], int n) {
	int i = 0;
	int j, jj;
	int max, step = 1;
	
	if (n < 2) return 0;
	if (n == 2) return 1;

	max = A[0];

	do {
		if (max >= n - 1) return step;
		for (j = i + 1; j <= i + A[i] && j < n; j++) {
			if (max < j + A[j]) {
				max = j + A[j];
				jj = j;
			}
		}
		i = jj;
		step++;		
	}while (1);
}

vector<vector<int> > permute(vector<int> &num) {
	vector<vector<int> > x;
	vector<vector<int> > r;
	vector<int> tmp(num);
	vector<int>::iterator it;
	int k;

	if (num.size() == 0) return r;
	if (num.size() == 1) {
		r.push_back(num);
		return r;
	} 

	k = tmp.back();
	tmp.pop_back();

	x = permute(tmp);
	for (int i = 0; i < x.size(); i++) {
		tmp = x.at(i);
		it = tmp.begin();
		for (int j = 0; j <= tmp.size(); j++) {
			it = tmp.begin();
			it = tmp.insert(it + j, k);
			r.push_back(tmp);
			tmp.erase(it);
		}
	}
	return r;
}

vector<vector<int> > permuteUnique(vector<int> &num) {
	vector<vector<int> > x;
	vector<vector<int> > r;
	vector<int> tmp(num);
	vector<int>::iterator it;
	int k, n;

	if (num.size() == 0) return r;
	if (num.size() == 1) {
		r.push_back(num);
		return r;
	} 

	k = tmp.back();
	tmp.pop_back();

	x = permuteUnique(tmp);
	for (int i = 0; i < x.size(); i++) {
		tmp = x.at(i);
		it = tmp.begin();
		for (int j = 0; j <= tmp.size(); j++) {
			it = tmp.begin();
			it = tmp.insert(it + j, k);
			r.push_back(tmp);
			tmp.erase(it);
			if (j < tmp.size() && k == tmp.at(j)) break;
		}
	}
	return r;
}

void rotate(vector<vector<int> > &matrix) {
	int n = matrix.size();
	int i, j, t, k, l;

	if (n < 2) return;

	if (n % 2 == 0) {
		l = k = n / 2;
	}
	else {
		k = (n + 1) / 2;
		l = k - 1;
	}
	for (i = 0; i < k; i++)
		for (j = 0; j < l; j++) {
			t = matrix.at(i).at(j);
			matrix.at(i).at(j) = matrix.at(n - 1 - j).at(i);
			matrix.at(n - 1 - j).at(i) = matrix.at(n - 1 - i).at(n - 1 - j);
			matrix.at(n - 1 - i).at(n - 1 - j) = matrix.at(j).at(n - 1 - i);
			matrix.at(j).at(n - 1 - i) = t;
		}

	return;
}

double pow1(double x, int n) {
	unsigned int i = 0;
	double tmp, result;
	int flag = 0;

	if (n == 0) return 1;
	if (n < 0 && n != INT_MIN) {
		x = 1 / x;
		n = -n;
	}
	else if (n == INT_MIN) {
		x = 1 / x;
		n = INT_MAX;
		flag = 1;
	}

	tmp = x;
	result = 1.0;
	while ((1<<i) <= (unsigned int)n) 
		i++;


	for (int j = 0; j < i; j++) {
		if (n & (1<<j))
			result *= tmp;
		tmp = tmp * tmp;
	}
	if (flag) return result*x;
	return result;
}

int maxSubArray(int A[], int n) {
	int x, y, p, tmp, max = INT_MIN;

	x = 0; y = n - 1;
	tmp = INT_MIN;
	while (A[x] <= 0 && x < n) {
		if (tmp < A[x]) tmp = A[x];
		x++;		
	}
	while (A[y] <= 0 && y >= 0) y--;

	if (x == n) {
		return tmp;
	}
	if (x == y) return A[x];

	do {
		p = x;
		tmp = A[p];
		while (tmp > 0 && p != y) {
			if (tmp > max) max = tmp;
			tmp += A[++p];			
		}
		if (tmp <= 0) x = p + 1;
	} while (p != y);

	do {
		p = y;
		tmp = A[p];
		while (tmp > 0 && p != x) {
			if (tmp > max) max = tmp;
			tmp += A[--p];
		}
		if (tmp <= 0) y = p - 1;
	} while (p != x);

	tmp = 0;
	for (p = x; p <= y; p++) {
		tmp += A[p];
	}

	if (tmp > max) max = tmp;
	return max;
}

vector<int> spiralOrder(vector<vector<int> > &matrix) {
	vector<int> result;
	int left, right, top, down, count = 0;
	int direction = 1;

	int m, n, i, j;
	n = matrix.size();
	if (n == 0) return result;
	if (n == 1) return matrix.at(0);

	m = matrix.at(0).size();

	left = -1; 
	right = m;
	top = 0; 
	down = n;

	i = 0; j = 0;

	while (count < m * n) {
		result.push_back(matrix.at(j).at(i));
		count++;
		if (direction == 1) {
			if (i < right - 1) i++;
			else {
				right--;
				j++;
				direction = 2;
			}
		}
		else if (direction == 2) {
			if (j < down - 1) j++;
			else {
				down--;
				i--;
				direction = 3;
			}
		}
		else if (direction == 3) {
			if (i > left + 1) i--;
			else {
				left++;
				j--;
				direction = 4;
			}
		}
		else if (direction == 4) {
			if (j > top + 1) j--;
			else {
				top++;
				i++;
				direction = 1;
			}
		}
	}
	return result;
}

bool canJump(int A[], int n) {
	if (n == 1) return true;
	if (A[0] == 0) return false;
	if (A[0] >= n-1) return true;

	int i = 0, max = A[0], jj = 0, j;

	do {
		if (max >= n - 1) return true;
		for (j = i + 1; j <= i + A[i] && j < n; j++) {
			if (max <= j + A[j]) {
				max = j + A[j];
				jj = j;
			}
		}
		i = jj;
		if (A[i] == 0) return false;
	} while (1);
}

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

vector<Interval> merge(vector<Interval> &intervals) {
    vector<Interval> w;
	vector<Interval> t;
	Interval itr;
	int i, j;

	w.push_back(Interval(INT_MIN, INT_MAX));

	for (i = 0; i < intervals.size(); i++) {
		t.clear();
		itr = intervals.at(i);
		for (j = 0; j < w.size(); j++) {
			if (itr.start > w.at(j).end || itr.end < w.at(j).start) {
				t.push_back(w.at(j));
			}
			else if (itr.start <= w.at(j).start && itr.end >= w.at(j).end) {
				continue;
			}
			else if (itr.start > w.at(j).start && itr.end < w.at(j).end) {
				t.push_back(Interval(w.at(j).start, itr.start));
				t.push_back(Interval(itr.end, w.at(j).end));
			}
			else if (itr.start > w.at(j).start && itr.end >= w.at(j).end) {
				t.push_back(Interval(w.at(j).start, itr.start));
			}
			else if (itr.start <= w.at(j).start && itr.end < w.at(j).end) {
				t.push_back(Interval(itr.end, w.at(j).end));
			}
		}
		w = t;
	}
	t.clear();
	for (i = 0; i < w.size() - 1; i++) {
		t.push_back(Interval(w.at(i).end, w.at(i + 1).start));
	}
	return t;
}

vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
    vector<Interval> w;
	vector<Interval> t;
	vector<Interval> xx(intervals);
	Interval itr, last;
	int i, j;

	w.push_back(Interval(INT_MIN, INT_MAX));
	//xx.push_back(newInterval);

	for (i = 0; i < xx.size(); i++) {
		last = w.back();
		w.pop_back();

		itr = xx.at(i);
		if (itr.start > last.end || itr.end < last.start) {	//impossible
			w.push_back(last);
		}
		else if (itr.start <= last.start && itr.end >= last.end) {	//impossible
			continue;
		}
		else if (itr.start > last.start && itr.end < last.end) {
			w.push_back(Interval(last.start, itr.start));
			w.push_back(Interval(itr.end, last.end));
		}
		else if (itr.start > last.start && itr.end >= last.end) {	//impossible
			w.push_back(Interval(last.start, itr.start));
		}
		else if (itr.start <= last.start && itr.end < last.end) {
			w.push_back(Interval(itr.end, last.end));
		}
	}

	t.clear();
	for (j = 0; j < w.size(); j++) {
		itr = newInterval;
		if (itr.start > w.at(j).end || itr.end < w.at(j).start) {
			t.push_back(w.at(j));
		}
		else if (itr.start <= w.at(j).start && itr.end >= w.at(j).end) {
			continue;
		}
		else if (itr.start > w.at(j).start && itr.end < w.at(j).end) {
			t.push_back(Interval(w.at(j).start, itr.start));
			t.push_back(Interval(itr.end, w.at(j).end));
		}
		else if (itr.start > w.at(j).start && itr.end >= w.at(j).end) {
			t.push_back(Interval(w.at(j).start, itr.start));
		}
		else if (itr.start <= w.at(j).start && itr.end < w.at(j).end) {
			t.push_back(Interval(itr.end, w.at(j).end));
		}
	}
	w = t;

	t.clear();
	for (i = 0; i < w.size() - 1; i++) {
		t.push_back(Interval(w.at(i).end, w.at(i + 1).start));
	}
	return t;
}

int lengthOfLastWord(const char *s) {
	int len = strlen(s);
	int count = 0;
	int mode = 0;
	const char * p = s + len - 1;
	if (len == 0) return 0;

	do {
		if ((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z')) {
			mode = 1;
			count++;
		}
		else {
			if (mode == 1) return count;
		}
	} while (p-- != s);

	return count;
}

vector<vector<int> > generateMatrix(int n) {
	vector<vector<int>> r;
	vector<int> row;

	if (n == 0) return r;
	row.assign(n, 0);
	r.assign(n, row);

	int left, right, top, down, count = 0;
	int direction = 1;

	int i, j, m = n;
	left = -1; 
	right = m;
	top = 0; 
	down = n;

	i = 0; j = 0;

	while (count < m * n) {
		r.at(j).at(i) = count + 1;
		count++;
		if (direction == 1) {
			if (i < right - 1) i++;
			else {
				right--;
				j++;
				direction = 2;
			}
		}
		else if (direction == 2) {
			if (j < down - 1) j++;
			else {
				down--;
				i--;
				direction = 3;
			}
		}
		else if (direction == 3) {
			if (i > left + 1) i--;
			else {
				left++;
				j--;
				direction = 4;
			}
		}
		else if (direction == 4) {
			if (j > top + 1) j--;
			else {
				top++;
				i++;
				direction = 1;
			}
		}
	}

	return r;
}

string getPermutation(int n, int k) {
	string result = "";
	if (n > 9) return result;

	int x[10], i, j, kk;
	int c[10];
	char num[10];

	x[0] = 1;
	num[0] = '0';
	for (i = 1; i < 10; i++) {
		x[i] = x[i - 1] * i;
		num[i] = '0' + i;
	}

	kk = k - 1;
	for (i = 9; i >= 0; i--) {
		c[i] = kk / x[i] + 1;
		kk = kk % x[i];
	}

	int count;
	for (i = n - 1; i >= 0; i--) {
		count = 0;
		for (j = 1; j <= n; j++) {
			if (num[j] > '0') {
				count++;
				if (count == c[i]) {
					result += (num[j]);
					num[j] = '0';
					break;
				}
			}
		}
	}
	return result;
}

ListNode *rotateRight(ListNode *head, int k) {
	ListNode *p, *q, *last;
	int len, r, i;

	if (head == NULL) return head;
	p = head;
	len = 0;
	while (p != NULL) {
		if (p->next == NULL) last = p;
		p = p->next;
		len ++;
	}
	if (k % len == 0) return head;
	else r = k % len;
	
	r = len - r;
	i = 0;
	p = head;
	while (i < r) {
		q = p;
		p = p->next;
		i++;
	}

	q->next = NULL;
	last->next = head;
	return p;
}

int uniquePaths(int m, int n) {
	int * x = new int[m * n];
	int i, j;

	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++) {
			if (i == 0) x[i * n + j] = 1;
			else if (j == 0) x[i * n + j] = 1;
			else x[i * n + j] = x[(i - 1) * n + j] + x[i * n + j - 1];
		}

	i = x[m * n - 1];
	delete x;
	return i;
}

int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
	int m, n, i, j;
	vector<vector<int>> c(obstacleGrid);

	m = c.size();
	if (m == 0) return 0;
	n = c.at(0).size();

	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++) {
			if (c.at(i).at(j) == 0) c.at(i).at(j) = -1;
			else c.at(i).at(j) = 0;
		}
	
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++) {
			if (c.at(i).at(j) != 0) {
				if (i == 0 && j == 0) c.at(i).at(j) = 1;
				else if (i == 0) c.at(i).at(j) = c.at(i).at(j - 1);
				else if (j == 0) c.at(i).at(j) = c.at(i - 1).at(j);
				else c.at(i).at(j) = c.at(i).at(j - 1) + c.at(i - 1).at(j);
			}
		}
	return c.at(m - 1).at(n - 1);
}

int minPathSum(vector<vector<int> > &grid) {
	int m, n, i, j;
	vector<vector<int>> c(grid);

	m = c.size();
	if (m == 0) return 0;
	n = c.at(0).size();

	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++) {
			if (i == 0 && j == 0) ;
			else if (i == 0) c.at(i).at(j) += c.at(i).at(j - 1);
			else if (j == 0) c.at(i).at(j) += c.at(i - 1).at(j);
			else c.at(i).at(j) += min(c.at(i).at(j - 1), c.at(i - 1).at(j));
		}
	return c.at(m - 1).at(n - 1);
}

ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
    ListNode * head, *p, *q, *current;

	p = l1; q = l2;
	if (p == NULL && q == NULL) return NULL;
	if (p == NULL) return q;
	if (q == NULL) return p;

	if (p->val < q->val) {
		head = p;
		current = p;
		p = p->next;
	}
	else {
		head = q;
		current = q;
		q = q->next;
	}
	
	while (p != NULL && q != NULL) {
		if (p->val < q->val) {
			current->next = p;
			current = p;
			p = p->next;
		}
		else {
			current->next = q;
			current = q;
			q = q->next;
		}
	}

	if (p == NULL) current->next = q;
	else if (q == NULL) current->next = p;

	return head;
}

string addBinary(string a, string b) {
	string result = "";
	int aa, bb, flag = 0;
	
	while (a.size() > 0 || b.size() > 0 ) {
		aa = bb = 0;		
		if (a.size() > 0) {
			if (a.back() == '1') aa = 1;
			a.pop_back();
		}
		if (b.size() > 0) {
			if (b.back() == '1') bb = 1;
			b.pop_back();
		}
		if ((aa + bb + flag) % 2 == 1) {
			result.insert((string::size_type)0, 1, '1');
		}
		else {
			result.insert((string::size_type)0, 1, '0');
		}
		if (aa + bb + flag >= 2) {
			flag = 1;
		}
		else {
			flag = 0;
		}
	}
	if (flag) result.insert((string::size_type)0, 1, '1');
	
	return result;
}

bool _isValidSudoku(vector<vector <char>> &board, vector<int> &v) {
	int i, j, check;
	int y, x, b;

	if (v.size() != 27) return false;
	if (board.size() != 9) return false;
	if (board.at(0).size() != 9) return false;

	for (j = 0; j < 9; j++)
		for (i = 0; i < 9; i++) {
			if (board.at(j).at(i) == '.') {
				check = v.at(j) | v.at(i + 9) | v.at(18 + 3 * (j / 3) + i / 3);
				
				for (int k = 0; k < 9 ; k++) {
					if (((1 << k) & check) == 0) {
						board.at(j).at(i) = '1' + k;
						y = v.at(j);
						x = v.at(i + 9);
						b = v.at(18 + 3 * (j / 3) + i / 3);
						
						v.at(j) |= (1 << k);
						v.at(i + 9) |= (1 << k);
						v.at(18 + 3 * (j / 3) + i / 3) |= (1 << k);

						if (_isValidSudoku(board, v)) return true;

						v.at(j) = y;
						v.at(i + 9) = x;
						v.at(18 + 3 * (j / 3) + i / 3) = b;
					}
				}
				board.at(j).at(i) = '.';
				return false;
			}
		}
	return true;
}
bool isValidSudoku(vector<vector<char> > &board) {
	int i, j, k, m;
	vector<int> v;

	v.assign(27, 0);

	if (board.size() != 9) return false;
	if (board.at(0).size() != 9) return false;

	for (j = 0; j < 9; j++) {
		for (i = 0; i < 9; i++) {
			if (board.at(j).at(i) != '.') {
				k = board.at(j).at(i) - '1';
				if (k < 0 || k > 8) return false;
				m = 1 << k;
				if ((v.at(j) & m) != 0 || (v.at(i + 9) & m) != 0 ||
					(v.at(18 + 3 * (j / 3) + i / 3) & m) != 0) 
					return false;
				v.at(j) |= m;
				v.at(i + 9) |= m;
				v.at(18 + 3 * (j / 3) + i / 3) |= m;
			}
		}
	}
	m = 0;
	for (i = 0; i < 9; i++) {
		m += v.at(i);
	}

	if (m == 0) return true;
	return _isValidSudoku(board, v);
}

void solveSudoku(vector<vector<char> > &board) {
	int i, j, k, m;
	vector<int> v;

	v.assign(27, 0);

	if (board.size() != 9) return;
	if (board.at(0).size() != 9) return;

	for (j = 0; j < 9; j++) {
		for (i = 0; i < 9; i++) {
			if (board.at(j).at(i) != '.') {
				k = board.at(j).at(i) - '1';
				if (k < 0 || k > 8) return;
				m = 1 << k;
				if ((v.at(j) & m) != 0 || (v.at(i + 9) & m) != 0 ||
					(v.at(18 + 3 * (j / 3) + i / 3) & m) != 0) 
					return;
				v.at(j) |= m;
				v.at(i + 9) |= m;
				v.at(18 + 3 * (j / 3) + i / 3) |= m;
			}
		}
	}
	m = 0;
	for (i = 0; i < 9; i++) {
		m += v.at(i);
	}

	if (m == 0) return;
	_isValidSudoku(board, v);
	return;
}

int _tmain(int argc, _TCHAR* argv[])
{

	/* for is valid sukodu
	vector<char> t;
	vector<vector<char>> tt;
	string s;
	int ii;

	t.assign(9, '.');
	tt.assign(9, t);

	ii = 0;
	s = ".2.489.7.";
	for (int j = 0; j < 9; j++ ) tt.at(ii).at(j) = s.at(j);
	ii = 1;
	s = "59.27....";
	for (int j = 0; j < 9; j++ ) tt.at(ii).at(j) = s.at(j);
	ii = 2;
	s = "14....8..";
	for (int j = 0; j < 9; j++ ) tt.at(ii).at(j) = s.at(j);
	ii = 3;
	s = "..4.1....";
	for (int j = 0; j < 9; j++ ) tt.at(ii).at(j) = s.at(j);
	ii = 4;
	s = "....267..";
	for (int j = 0; j < 9; j++ ) tt.at(ii).at(j) = s.at(j);
	ii = 5;
	s = ".19..4...";
	for (int j = 0; j < 9; j++ ) tt.at(ii).at(j) = s.at(j);
	ii = 6;
	s = "..8.5.4..";
	for (int j = 0; j < 9; j++ ) tt.at(ii).at(j) = s.at(j);
	ii = 7;
	s = "....9....";
	for (int j = 0; j < 9; j++ ) tt.at(ii).at(j) = s.at(j);
	ii = 8;
	s = "4........";
	for (int j = 0; j < 9; j++ ) tt.at(ii).at(j) = s.at(j);


	isValidSudoku(tt);
	*/
/*
".2.489.7.",
"59.27....",
"14....8..",
"..4.1....",
"....267..",
".19..4...",
"..8.5.4..",
"....9....",
"4........"
*/
	/* for get Permutation
	cout<<' '<<getPermutation(4, 5).c_str();
	*/
	/* for generateMatrix
	generateMatrix(3);
	*/
	/* for merge
	vector<Interval> k;
	k.push_back(Interval(1,4));
	k.push_back(Interval(5,6));
	merge(k);
	*/

	/* for maxSubArray
	int A[8] = {3,2,-3,-1,1,-3,1,-1};
	maxSubArray(A, 8);
	*/
	/* for pow
	pow1 (3, 5);
	*/
	/* for jump
	int A[12] = {5,9,3,2,1,0,2,3,3,1,0,0};
	jump(A, 12);
	*/
	/* for WildChar match
	isWildCharMatch2("ab", "ab**");
	*/
	//isWCMatch("ddjfaldjfla", "**aa*****ba*a*bb**aa*ab****a*aaaaaa***a*aaaa**bbabb*b*b**aaaaaaaaa*a********ba*bbb***a*ba*bb*bb**a*b*bb");
	//bool b = isWildCharMatch("abcd", "a*d");
	/* for multiply
	cout<<' '<<multiply("123456", "99899").c_str();
	*/
	/* for first missing positive
	int A[] = {1, 2, 3, 4, 5};
	firstMissingPositive(A, 5);
	*/

	/* for combinationSum2
	vector<int> t;
	t.push_back(2);
	t.push_back(2);
	t.push_back(3);
	t.push_back(5);
	t.push_back(3);

	combinationSum2(t, 8);
	*/

	/* for combinationSum
	vector<int> t;
	t.push_back(2);
	t.push_back(3);
	t.push_back(5);

	combinationSum(t, 8);
	*/
	/* for countAndSay
	cout <<' '<<countAndSay(6).c_str();	
	cout <<' '<<countAndSay(7).c_str();	
	cout <<' '<<countAndSay(8).c_str();	
	*/
	/* for search
	int A[7] = {3, 5, 1, 2, 2, 4, 5};
	cout << ' '<<searchQ(A, 3, 1);
	*/

	/* for longest Valid Parentheses
	cout <<' '<<longestValidParentheses("(()((");
	*/
	/* for findSubstring
	vector<string> kk;
	kk.push_back("A");
	kk.push_back("AA");
	findSubstring("CCAAAA", kk);
	*/
	/* for divide
	divide(100, 33);
	*/
	/* for strStr
	strStr("mississippi", "a");
	*/
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
