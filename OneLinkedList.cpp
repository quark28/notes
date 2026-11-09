#include <iostream>
#include <string>

template <typename NODE_VALUE_TYPE>
class OneLinkedList {
private:

	struct Node {
		Node* next;
		NODE_VALUE_TYPE value;

		Node(Node* next_node_ptr, const NODE_VALUE_TYPE& node_value) : next(next_node_ptr), value(node_value) {}
		Node(Node* next_node_ptr) : next(next_node_ptr) {}
	};

	Node head;
	Node* tail;
	size_t len;

public:
	OneLinkedList() : head(Node(nullptr)), tail(&head), len(0) {}
	~OneLinkedList() {
		Clear();
	}

	void PushForward(const NODE_VALUE_TYPE& value) {
		++len;
		Node* temp_ptr = new Node(head.next, value);
		head.next = temp_ptr;
		if (len == 1) {
			tail = head.next;
		}
	}
	bool DeleteByKey(const NODE_VALUE_TYPE& key) {
		Node* prev_node = &head, * cur_node = head.next;

		while (cur_node != nullptr) {
			if ((*cur_node).value == key) {
				--len;
				(*prev_node).next = (*cur_node).next;
				if (tail == cur_node) {
					tail = prev_node;
				}
				delete cur_node;
				return true;
			}
			prev_node = (*prev_node).next; cur_node = (*cur_node).next;
		}
		return false;
	}
	void PrintToConsole() const {
		Node* cur_node = head.next;
		std::cout << '[';
		while (cur_node != nullptr) {
			std::cout << ' ' << (*cur_node).value << ' ';
			cur_node = (*cur_node).next;
		}
		std::cout << ']';
	}

	bool operator==(const OneLinkedList& other) const {
		if ((*this).len != other.len) {
			return false;
		}

		const Node* this_node_ptr = head.next, * other_node_ptr = other.head.next;
		while (this_node_ptr != nullptr) {
			if ((*this_node_ptr).value != (*other_node_ptr).value) {
				return false;
			}
			other_node_ptr = (*other_node_ptr).next; this_node_ptr = (*this_node_ptr).next;
		}
		return true;
	}
	void AddLastFrom(const OneLinkedList& other) {
		if (other.len != 0) {
			++len;
			(*tail).next = new Node(nullptr, (*other.tail).value);
			tail = (*tail).next;
		}
	}
	void DeleteAllDigits() {

		Node* prev_node = &head, * cur_node = head.next;

		while (cur_node != nullptr) {
			if ((*cur_node).value >= '0' and (*cur_node).value <= '9') {
				(*prev_node).next = (*cur_node).next;
				if (cur_node == tail) {
					tail = prev_node;
				}
				--len;
				delete cur_node;
				cur_node = (*prev_node).next;
			}
			else {
				prev_node = (*prev_node).next; cur_node = (*cur_node).next;
			}
		}
	}

	void Clear() {
		Node* cur = head.next;
		while (cur != nullptr) {
			Node* next = (*cur).next;
			delete cur;
			cur = next;
		}
		head.next = nullptr;
		tail = &head;
		len = 0;
	}

	OneLinkedList(const OneLinkedList&) = delete;
	OneLinkedList& operator=(const OneLinkedList&) = delete;
};

using CharList = OneLinkedList<char>;

void Fill(CharList& list, const std::string& s) {
	list.Clear();
	for (int i = s.size() - 1; i >= 0; --i) {
		list.PushForward(s[i]);
	}
}

void PrintBoth(const CharList& L1, const CharList& L2) {
	std::cout << "L1 = "; L1.PrintToConsole(); std::cout << '\n';
	std::cout << "L2 = "; L2.PrintToConsole(); std::cout << '\n';
}

CharList& ChooseList(CharList& L1, CharList& L2) {
	int number;
	std::cout << "List (1 or 2): ";
	std::cin >> number;
	return (number == 1) ? L1 : L2;
}

void Report(const CharList& result, const CharList& expected) {
	std::cout << "  expected: "; expected.PrintToConsole(); std::cout << '\n';
	std::cout << "  result:   "; result.PrintToConsole(); std::cout << '\n';
	std::cout << "  " << (result == expected ? "OK" : "FAIL") << "\n\n";
}

void CasePushForward(const std::string& start, char value, const std::string& expected_str) {
	CharList list, expected;
	Fill(list, start);
	Fill(expected, expected_str);

	std::cout << "  list = "; list.PrintToConsole();
	std::cout << ", push '" << value << "'\n";

	list.PushForward(value);
	Report(list, expected);
}

void CaseDeleteByKey(const std::string& start, char key, const std::string& expected_str) {
	CharList list, expected;
	Fill(list, start);
	Fill(expected, expected_str);

	std::cout << "  list = "; list.PrintToConsole();
	std::cout << ", key '" << key << "'\n";

	bool found = list.DeleteByKey(key);
	std::cout << "  found: " << (found ? "yes" : "no") << '\n';
	Report(list, expected);
}

void CaseEqual(const std::string& s1, const std::string& s2, bool expected) {
	CharList a, b;
	Fill(a, s1);
	Fill(b, s2);

	std::cout << "  L1 = "; a.PrintToConsole();
	std::cout << ", L2 = "; b.PrintToConsole(); std::cout << '\n';

	bool result = (a == b);
	std::cout << "  expected: " << (expected ? "equal" : "not equal") << '\n';
	std::cout << "  result:   " << (result ? "equal" : "not equal") << '\n';
	std::cout << "  " << (result == expected ? "OK" : "FAIL") << "\n\n";
}

void CaseAddLastFrom(const std::string& s1, const std::string& s2, const std::string& expected_str) {
	CharList a, b, expected;
	Fill(a, s1);
	Fill(b, s2);
	Fill(expected, expected_str);

	std::cout << "  L1 = "; a.PrintToConsole();
	std::cout << ", L2 = "; b.PrintToConsole(); std::cout << '\n';

	a.AddLastFrom(b);
	Report(a, expected);
}

void CaseDeleteAllDigits(const std::string& start, const std::string& expected_str) {
	CharList list, expected;
	Fill(list, start);
	Fill(expected, expected_str);

	std::cout << "  list = "; list.PrintToConsole(); std::cout << '\n';

	list.DeleteAllDigits();
	Report(list, expected);
}

void CasePrintToConsole(const std::string& start, const std::string& expected) {
	CharList list;
	Fill(list, start);

	std::cout << "  list from \"" << start << "\"\n";
	std::cout << "  expected: " << expected << '\n';
	std::cout << "  result:   "; list.PrintToConsole(); std::cout << "\n\n";
}

void TestPrintToConsole() {
	std::cout << "\nTEST: PrintToConsole\n";
	CasePrintToConsole("abc", "[ a  b  c ]");
	CasePrintToConsole("", "[]");
}

void TestPushForward() {
	std::cout << "\nTEST: PushForward\n";
	CasePushForward("", 'a', "a");
	CasePushForward("bc", 'a', "abc");
}

void TestDeleteByKey() {
	std::cout << "\nTEST: DeleteByKey\n";
	CaseDeleteByKey("abca", 'a', "bca");
	CaseDeleteByKey("abc", 'c', "ab");
	CaseDeleteByKey("abc", 'z', "abc");
	CaseDeleteByKey("", 'a', "");
}

void TestEqual() {
	std::cout << "\nTEST: L1 == L2\n";
	CaseEqual("abc", "abc", true);
	CaseEqual("abc", "abd", false);
	CaseEqual("ab", "abc", false);
	CaseEqual("", "", true);
}

void TestAddLastFrom() {
	std::cout << "\nTEST: AddLastFrom\n";
	CaseAddLastFrom("ab", "xyz", "abz");
	CaseAddLastFrom("", "q", "q");
	CaseAddLastFrom("ab", "", "ab");
}

void TestDeleteAllDigits() {
	std::cout << "\nTEST: DeleteAllDigits\n";
	CaseDeleteAllDigits("1a23b4", "ab");
	CaseDeleteAllDigits("abc", "abc");
	CaseDeleteAllDigits("123", "");
	CaseDeleteAllDigits("", "");
}

int main() {
	CharList L1, L2;

	int choice = -1;
	while (choice != 0) {
		std::cout << "\n 1. Enter list\n"
			<< " 2. Push front\n"
			<< " 3. Delete by key\n"
			<< " 4. Print lists\n"
			<< " 5. L1 == L2\n"
			<< " 6. Add last of L2 to end of L1\n"
			<< " 7. Delete digits from L2\n"
			<< " 8. TEST: PushForward\n"
			<< " 9. TEST: DeleteByKey\n"
			<< "10. TEST: L1 == L2\n"
			<< "11. TEST: AddLastFrom\n"
			<< "12. TEST: DeleteAllDigits\n"
			<< "13. TEST: PrintToConsole\n"
			<< " 0. Exit\n"
			<< "> ";

		if (!(std::cin >> choice)) {
			break;
		}

		switch (choice) {
		case 1: {
			CharList& list = ChooseList(L1, L2);
			std::cout << "Chars without spaces ('-' for empty): ";
			std::string s;
			std::cin >> s;
			Fill(list, s == "-" ? "" : s);
			PrintBoth(L1, L2);
			break;
		}
		case 2: {
			CharList& list = ChooseList(L1, L2);
			std::cout << "Char: ";
			char c;
			std::cin >> c;
			list.PushForward(c);
			PrintBoth(L1, L2);
			break;
		}
		case 3: {
			CharList& list = ChooseList(L1, L2);
			std::cout << "Key: ";
			char key;
			std::cin >> key;
			if (!list.DeleteByKey(key)) {
				std::cout << "Not found\n";
			}
			PrintBoth(L1, L2);
			break;
		}
		case 4:
			PrintBoth(L1, L2);
			break;
		case 5:
			PrintBoth(L1, L2);
			std::cout << (L1 == L2 ? "Equal\n" : "Not equal\n");
			break;
		case 6:
			L1.AddLastFrom(L2);
			PrintBoth(L1, L2);
			break;
		case 7:
			L2.DeleteAllDigits();
			PrintBoth(L1, L2);
			break;
		case 8:  TestPushForward();     break;
		case 9:  TestDeleteByKey();     break;
		case 10: TestEqual();           break;
		case 11: TestAddLastFrom();     break;
		case 12: TestDeleteAllDigits(); break;
		case 13: TestPrintToConsole();  break;
		}
	}
	return 0;
}