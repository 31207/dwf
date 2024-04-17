#include "dwf.h"
unsigned int count = 0;
dwf::Bigint::Bigint()
{
	num = "0";
	isNegative = false;
}
dwf::Bigint::Bigint(std::string num_str)
{
	if (!checkNum(num_str))
	{
		this->num = "0";
		isNegative = false;
		return;
	}
	else if (num_str[0] == '-')
	{
		num_str = num_str.substr(1);
		num_str = cutZero(num_str);
		this->num = num_str;
		isNegative = true;
	}
	else
	{
		num_str = cutZero(num_str);
		this->num = num_str;
		isNegative = false;
	}
}
dwf::Bigint::~Bigint()
{
}

void dwf::Bigint::plus(int addend) // addend 加数
{
	std::string addend_str = std::to_string(addend);
	plus(addend_str);
}

void dwf::Bigint::plus(std::string addend_str) // addend 加数
{
	if (!checkNum(addend_str))
	{
		this->num = "0";
		return;
	}
	addend_str = cutZero(addend_str);
	std::string result = "";
	unsigned int len_num = this->num.length();
	unsigned int len_addend = addend_str.length();
	int count;
	if (len_num > len_addend)
	{
		count = len_num;
		for (int i = 0; i < len_num - len_addend; i++)
		{
			addend_str = "0" + addend_str;
		}
	}
	else
	{
		count = len_addend;
		for (int i = 0; i < len_addend - len_num; i++)
		{
			num = "0" + num;
		}
	}
	int carry = 0; // carry 进位
	auto j = addend_str.begin();
	std::reverse(num.begin(), num.end());
	std::reverse(addend_str.begin(), addend_str.end());
	for (auto i = this->num.begin(); i != this->num.end(); ++i, ++j)
	{
		int a = (*i) - 0x30; // ascii中，数字对应的字符码减去0x30即为对应数字
		int b = (*j) - 0x30;
		int sum = a + b + carry;
		if (sum >= 10)
		{
			carry = 1;
			sum -= 10;
			result += char(sum + 0x30);
		}
		else
		{
			carry = 0;
			result += char(sum + 0x30);
		}
	}
	reverse(result.begin(), result.end());
	if (carry != 0)
	{
		result = char(carry + 0x30) + result;
	}
	num = result;
}

void dwf::Bigint::multiply(int num)
{
	std::string multiplier_str = std::to_string(num);
	multiply(multiplier_str);
}

void dwf::Bigint::multiply(std::string multiplier_str)
{
	if (!checkNum(multiplier_str))
	{
		this->num = "0";
		return;
	}
	multiplier_str = cutZero(multiplier_str);
	int* num_list = cutStr2Piece(num);
	int* multiplier_str_list = cutStr2Piece(multiplier_str);
	reverseInt(num_list, num.length());
	reverseInt(multiplier_str_list, multiplier_str.length());
	int num_list_sum = 0;
	int multiplier_str_list_sum = 0;
	std::string result_str;
	for (int i = 0; i < num.length(); i++)
	{
		num_list_sum += num_list[i];
	}
	for (int i = 0; i < multiplier_str.length(); i++)
	{
		multiplier_str_list_sum += multiplier_str_list[i];
	}
	if (num_list_sum < multiplier_str_list_sum)
	{
		std::string* mid_result = new std::string[num.length()];
		for (int i = 0; i < num.length(); i++)
		{
			dwf::Bigint temp;
			for (int j = 0; j < num_list[i]; j++)
			{
				temp.plus(multiplier_str);
			}
			std::string temp_str = temp.tostring();
			for (int j = 0; j < i; j++)
			{
				temp_str += "0";
			}
			mid_result[i] = temp_str;
		}
		dwf::Bigint result;
		for (int i = 0; i < num.length(); i++)
		{
			result.plus(mid_result[i]);
		}
		result_str = result.tostring();
		delete[] mid_result;
	}
	else
	{
		std::string* mid_result = new std::string[multiplier_str.length()];
		for (int i = 0; i < multiplier_str.length(); i++)
		{
			dwf::Bigint temp;
			for (int j = 0; j < multiplier_str_list[i]; j++)
			{
				temp.plus(num);
			}
			std::string temp_str = temp.tostring();
			for (int j = 0; j < i; j++)
			{
				temp_str += "0";
			}
			mid_result[i] = temp_str;
		}
		dwf::Bigint result;
		for (int i = 0; i < multiplier_str.length(); i++)
		{
			result.plus(mid_result[i]);
		}
		result_str = result.tostring();
		delete[] mid_result;
	}
	delete[] num_list;
	delete[] multiplier_str_list;
	num = result_str;
}
void dwf::Bigint::subtraction(int num)
{
	std::string subtractor_str = std::to_string(num);
	subtraction(subtractor_str);
}

void dwf::Bigint::subtraction(std::string subtractor_str)       //只支持正的大数减正的小数
{
	if (!checkNum(subtractor_str))
	{
		this->num = "0";
		return;
	}
	subtractor_str = cutZero(subtractor_str);
	std::string result = "";

	unsigned int len_num = this->num.length();
	unsigned int len_subtractor = subtractor_str.length();
	for (int i = 0; i < len_num - len_subtractor; i++)
	{
		subtractor_str = "0" + subtractor_str;
	}


	int carry = 0;
	auto j = subtractor_str.begin();
	std::reverse(num.begin(), num.end());
	std::reverse(subtractor_str.begin(), subtractor_str.end());
	for (auto i = this->num.begin(); i != this->num.end(); ++i, ++j)
	{
		int a = (*i) - 0x30; // ascii中，数字对应的字符码减去0x30即为对应数字
		int b = (*j) - 0x30;
		int sum = a - b + carry;
		if (sum < 0)
		{
			sum += 10;
			carry = -1;
			result.push_back((char)(sum + 0x30));
		}
		else
		{
			carry = 0;
			result.push_back((char)(sum + 0x30));
		}
	}
	reverse(result.begin(), result.end());
	result = cutZero(result);
	this->num = result;
}

std::string dwf::Bigint::tostring() const
{
	if (this->isNegative)
	{
		return "-" + num;
	}
	else
	{
		return num;
	}

}

std::string dwf::Bigint::getNum() const
{
	return num;
}

int* dwf::Bigint::cutStr2Piece(std::string str)
{
	if (str == "")
	{
		return nullptr;
	}
	int* list = new int[str.length()];
	int j = 0;
	for (auto i = str.begin(); i != str.end(); ++i, j++)
	{
		list[j] = (*i) - 0x30;
	}
	return list;
}
void dwf::Bigint::reverseInt(int* list, int num)
{
	int temp;
	for (int i = num - 1, j = 0; i >= 0; i--, j++)
	{
		if (i < j)
		{
			break;
		}
		temp = list[j];
		list[j] = list[i];
		list[i] = temp;
	}
}

std::string dwf::Bigint::cutZero(std::string str)
{
	int j = 0;
	for (auto i = str.begin(); i != str.end(); ++i, j++)
	{
		if ((*i) != '0')
		{
			str = str.substr(j);
			return str;
		}
	}
	return "0";
}

bool dwf::Bigint::checkNum(std::string str)
{
	if (str == "" || str == "-")
	{
		return false;
	}
	auto i = str.begin();
	if ((*i) != '-' && ((*i) < '0' || (*i) > '9'))
	{
		return false;
	}
	++i;
	for (; i != str.end(); ++i)
	{
		if ((*i) < '0' || (*i) > '9')
		{
			return false;
		}
	}
	return true;
}

int dwf::Bigint::compare(const dwf::Bigint& a, const dwf::Bigint& b) const
{
	if (!a.isNegative && !b.isNegative)
	{
		if (a.num.length() > b.num.length())
		{
			return 1;
		}
		else if (a.num.length() < b.num.length())
		{
			return -1;
		}
		else
		{
			auto i = a.num.begin();
			auto j = b.num.begin();
			for (; i != a.num.end(); ++i, ++j)
			{
				if ((*i) != (*j))
				{
					if ((*i) > (*j))
					{
						return 1;
					}
					else
					{
						return -1;
					}
				}
			}
			return 0;
		}
	}
	else if (!a.isNegative && b.isNegative)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

bool dwf::Bigint::operator>(const dwf::Bigint& b) const
{
	if (compare(*this, b) == 1)
		return true;
	else
		return false;
}
bool dwf::Bigint::operator<(const dwf::Bigint& b) const
{
	if (compare(*this, b) == -1)
		return true;
	else
		return false;
}
bool dwf::Bigint::operator>=(const dwf::Bigint& b) const
{
	if (compare(*this, b) >= 0)
		return true;
	else
		return false;
}
bool dwf::Bigint::operator<=(const dwf::Bigint& b) const
{
	if (compare(*this, b) <= 0)
		return true;
	else
		return false;
}

dwf::Bigint dwf::Bigint::operator+(const dwf::Bigint& append) const
{
	if (this->getNum() == "0")
	{
		return append;
	}
	if (append.getNum() == "0")
	{
		return (*this);
	}
	if (this->isNegative == append.isNegative)
	{
		dwf::Bigint tmp(*this);
		tmp.plus(append.getNum());
		return tmp;
	}
	else
	{
		if (this->getNum() == append.getNum())      //相反数相加等于0
		{
			return dwf::Bigint();
		}
		if ((append < dwf::Bigint() && (*this) > -append) || ((*this) < dwf::Bigint() && -(*this) > append))
		{
			dwf::Bigint tmp(*this);
			tmp.subtraction(append.getNum());
			return tmp;
		}
		else if ((append < dwf::Bigint() && (*this) < -append) || ((*this) < dwf::Bigint() && -(*this) < append))
		{
			dwf::Bigint tmp(append);
			tmp.subtraction(this->getNum());
			return tmp;
		}
	}
	return dwf::Bigint("-1");       //一般不会出现这种情况
}

dwf::Bigint dwf::Bigint::operator-(const dwf::Bigint& subtractor) const
{
	dwf::Bigint tmp = (*this) + (-subtractor);
	return tmp;
}

dwf::Bigint dwf::Bigint::operator*(const dwf::Bigint& multiplier) const
{
	if (this->getNum() == "0" || multiplier.getNum() == "0")
	{
		return dwf::Bigint();
	}
	if (this->isNegative == multiplier.isNegative)
	{
		dwf::Bigint tmp(*this);
		tmp.multiply(multiplier.getNum());
		if (tmp > dwf::Bigint())
		{
			return tmp;
		}
		else
		{
			return -tmp;
		}
	}
	else
	{
		dwf::Bigint tmp(*this);
		tmp.multiply(multiplier.getNum());
		if (tmp > dwf::Bigint())
		{
			return -tmp;
		}
		else
		{
			return tmp;
		}
	}
	return dwf::Bigint();
}

dwf::Bigint dwf::Bigint::operator-() const
{
	dwf::Bigint tmp1(this->getNum());     //正数
	dwf::Bigint tmp2("-" + this->getNum());     //负数
	if ((*this) > dwf::Bigint())
	{
		return tmp2;
	}
	else
	{
		return tmp1;
	}
}

dwf::BinaryTree::BinaryTree()
{
	p_root = NULL;
}

dwf::BinaryTree::BinaryTree(int val)
{
	p_root = _newNode(val);
}

dwf::BinaryTree::BinaryTree(int* values,int n)
{
	p_root = NULL;
	for (size_t i = 0; i < n; i++)
	{
		_insert(values[i], p_root);
	}
}

dwf::BinaryTree::BinaryTree(std::vector<int> &values)
{
    p_root = NULL;
	for (size_t i = 0; i < values.size(); i++)
	{
		_insert(values[i], p_root);
	}
}

void dwf::BinaryTree::insert(int val)
{
	_insert(val, p_root);
}

void dwf::BinaryTree::setNodeVal(int val,int newval)
{
	_setNodeVal(val, newval, p_root);
}

void dwf::BinaryTree::preOrder()const
{
	_preOrder(p_root);
}

void dwf::BinaryTree::inOrder() const
{
	_inOrder(p_root);
}

void dwf::BinaryTree::postOrder() const
{
	_postOrder(p_root);
}

void dwf::BinaryTree::layerOrder() const
{
	_layerOrder(p_root);
}

void dwf::BinaryTree::_insert(int val,node*& p)
{
	if (p == NULL)
	{
		p = _newNode(val);
		return;
	}
	if (p->val > val)
	{
		_insert(val, p->lchild);
	}
	else
	{
		_insert(val, p->rchild);
	}

}

void dwf::BinaryTree::_preOrder(node* p) const
{
	if (p == NULL)return;
	std::cout << p->val << ' ';
	_preOrder(p->lchild);
	_preOrder(p->rchild);
}

void dwf::BinaryTree::_inOrder(node *p) const
{
	if (p == NULL)return;
	_inOrder(p->lchild);
	std::cout << p->val << ' ';
	_inOrder(p->rchild);
}

void dwf::BinaryTree::_postOrder(node *p) const
{
	if (p == NULL)return;
	_postOrder(p->lchild);
	_postOrder(p->rchild);
	std::cout << p->val << ' ';
}

void dwf::BinaryTree::_layerOrder(node* p) const
{
	std::vector<node*> list;
	list.push_back(p);
	while (!list.empty())
	{
		node* tmp = list[0];
		std::cout << tmp->val << ' ';
		list.erase(list.begin());
		if (tmp->lchild != NULL)
		{
			list.push_back(tmp->lchild);
		}
		if (tmp->rchild!=NULL)
		{
			list.push_back(tmp->rchild);
		}
	}

}

void dwf::BinaryTree::_setNodeVal(int val,int newval, node* p) const
{
	if (p == NULL)return;
	if (p->val == val)p->val = newval;
	_setNodeVal(val, newval, p->lchild);
	_setNodeVal(val, newval, p->rchild);
}

dwf::node* dwf::BinaryTree::_newNode(int val)
{
	node* tmp = new node;
	tmp->val = val;
	tmp->lchild = tmp->rchild = NULL;
	return tmp;
}

void dwf::bubbleSort(int* nums,int n)
{
	int tmp;
	bool isswap = false;
	for (size_t j = 0; j < n; j++)
	{
		isswap = false;
		for (size_t i = 0; i < n - 1; i++)
		{
			if (nums[i] < nums[i + 1])
			{
				isswap = true;
				tmp = nums[i];
				nums[i] = nums[i + 1];
				nums[i + 1] = tmp;
			}
		}
		if (!isswap)
		{
			break;
		}
	}

}

void dwf::fastSort(int* nums,int n)
{
	dwf::_fastSort(nums, n, 0, n - 1);
}

void dwf::_fastSort(int* nums, int n, int lo, int hi)
{
	if (lo >= hi)return;
	int l = lo, r = hi;
	int base = nums[(l + r) / 2];
	while (l < r)
	{
		while (l < r && nums[r] >= base)
		{
			r--;
		}
		if (l < r)
		{
			nums[l] = nums[r];
			l++;
		}
		while (l < r && nums[l] < base)
		{
			l++;
		}
		if (l < r)
		{
			nums[r] = nums[l];
			r--;
		}
	}
	nums[l] = base;
	dwf::_fastSort(nums, n, lo, l - 1);
	dwf::_fastSort(nums, n, l + 1, hi);
}
