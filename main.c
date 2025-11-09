#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char eng[100];
	char kor[100];
} word;

word voca[100];
int word_num = 0;
// 선택 할 수 있는 번호가 적힌 암기장의 첫 페이지를 재현한 함수 호출
void first_page() {
	printf("\n==========영어 단어 암기장==========\n\n");

	printf("0. 첫번째 페이지 호출\n");
	printf("1. 단어 추가\n");
	printf("2. 목록 보기\n");
	printf("3. 파일 저장\n");
	printf("4. 파일 불러오기\n");
	printf("5. 종료\n");
	printf("\n                -1-\n");
	printf("====================================\n");
}
// 단어 추가 함수
void voca_add() {
	printf("\n==========단어 추가 페이지==========\n\n");
	int cnt = 0;
	printf("%d번째 영어 단어 : ", word_num +1);
	fgets(voca[word_num].eng, 100, stdin);
	while (voca[word_num].eng[cnt] != '\0') {
		if (voca[word_num].eng[cnt] == '\n') {
			voca[word_num].eng[cnt] = '\0';
			break;
		}
		cnt++;
	}
	cnt = 0;

	printf("%d번째 한글 뜻 : ", word_num + 1);
	fgets(voca[word_num].kor, 100, stdin);
	while (voca[word_num].kor[cnt] != '\0') {
		if (voca[word_num].kor[cnt] == '\n') {
			voca[word_num].kor[cnt] = '\0';
			break;
		}
		cnt++;
	}
	word_num++;
	
	printf("====================================\n");
}
// 목록 보여주는 함수
void voca_list() {
	printf("\n==============단어  목록===========\n\n");
	printf("\n");
	for (int i = 0; i < word_num; i++) {
		printf("%d. %s   %s\n", i + 1, voca[i].eng, voca[i].kor);
	}
	printf("\n                -2-\n");
	printf("====================================\n");
}
// 파일에 단어 저장하는 함수
void file_save() {
	printf("\n====================================\n");

	if (word_num == 0) {
		printf("저장할 단어가 없습니다.\n");
		return;
	}

	FILE* file = fopen("voca_book.txt", "w");

	if (file == NULL) {
		printf("파일 저장에 실패했습니다.\n");
		return;
	}

	for (int i = 0; i < word_num; i++) {
		fprintf(file, "%s   %s\n", voca[i].eng, voca[i].kor);
	}
	fclose(file);
	printf("파일에 저장되었습니다\n");
	printf("====================================\n");
}
// 파일을 불러오는 함수
void file_load() {
	printf("\n====================================\n\n");

	printf("파일을 불러오고 있습니다.\n");

	FILE* file = fopen("voca_book.txt", "r");
	int j = 0;

	if (file == NULL) {
		printf("파일이 없습니다.\n");
		return;
	}

	for (int i = 0; i < word_num; i++) {
		fgets(voca[i].eng, 100, file);
		while (voca[i].eng[j] != '\0') {
			if (voca[i].eng[j] == '\n') {
				voca[i].eng[j] = '\0';
				break;
			}
			j++;
		}
		j = 0;

		fgets(voca[i].kor, 100, file);
		while (voca[i].kor[j] != '\0') {
			if (voca[i].kor[j] == '\n') {
				voca[i].kor[j] = '\0';
				break;
			}
			j++;
		}
	}
	fclose(file);
	printf("파일에서 무사히 불러왔습니다\n");
	printf("====================================\n");
}
// 입력 버퍼 지우는 함수
void clear_buffer(){
	int c;
	while (1) {
		c = getchar();
		if (c == '\n' || c == EOF) break;
	}
}

int main(void) {
	
	int choice = 0;
	first_page();                          // 선택 할 수 있는 번호가 적힌 암기장의 첫 페이지를 재현한 함수 호출
	
	while (1) {
		printf("\n번호 선택 : ");
		scanf("%d", &choice);
		clear_buffer();                   // 입력 버퍼 지우는 함수 호출

		switch (choice) {                 // 번호에 맞는 함수 호출
		case 0:
			first_page();
			break;
		case 1:
			voca_add();
			break;
		case 2:
			voca_list();
			break;
		case 3:
			file_save();
			break;
		case 4:
			file_load();
			break;
		case 5:
			printf("\n프로그램 종료\n");
			return 0;
		default:
			printf("\n잘못된 선택입니다.\n");
		}
	}
	return 0;
}