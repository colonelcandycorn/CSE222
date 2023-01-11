#include "gtest/gtest.h"
#include "main.h"
#include <string>

using namespace std;

TEST(DataNode, sentinal) {
	//arrange
	string s("SENTINAL");

	//act
	struct DataNode *newNode = init();
	string a(newNode->data);
	//assert
	ASSERT_EQ(s,a);
	cleanup(newNode);
}

TEST(DataNode, add1) {
	
	string s("Poop");
	char *a = &(s[0]);
	struct DataNode *sent = init();
	
	add(sent, a);
	
	string b(sent->next->data);

	ASSERT_EQ(s, b);
	cleanup(sent);
}

TEST(DataNode, add2) {
	string s("Poop");
	char *a = &(s[0]);
	string t("Open");
	char *b= &(t[0]);

	// act
	struct DataNode *sent = init();
	add(sent, a);
	add(sent, b);
	string first(sent->next->data);
	string second(sent->next->next->data);

	//assert
	ASSERT_EQ(t, first);
	ASSERT_EQ(s, second);
	cleanup(sent);
}

TEST(DataNode, print) {
	string s("Poop");
	char *a = &(s[0]);
	string t("Open");
	char *b= &(t[0]);
	string u("Queen");
	char *c = &(u[0]);
	string v("Baby");
	char *d = &(v[0]);

	// act
	struct DataNode *sent = init();
	add(sent, a);
	add(sent, b);
	add(sent, c);
	add(sent, d);

	print(sent);
	cleanup(sent);
}

TEST(DataNode, delete1) {
	string s("Poop");
	char *a = &(s[0]);
	string t("Open");
	char *b= &(t[0]);
	string u("Queen");
	char *c = &(u[0]);
	string v("Baby");
	char *d = &(v[0]);

	// act
	struct DataNode *sent = init();
	add(sent, a);
	add(sent, b);
	add(sent, c);
	add(sent, d);
	struct DataNode *del = init();
	add(del, a);
	add(del, b);
	add(del, c);
	add(del, d);

	myDelete(del, c);
	print(del);
	print(sent);

	for (int i = 0; i < 3; ++i) {
		sent = sent->next;
		del = del->next;
	}

	ASSERT_FALSE(del->next);
	ASSERT_TRUE(sent->next);
	cleanup(sent);
	cleanup(del);
}

int main(int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
