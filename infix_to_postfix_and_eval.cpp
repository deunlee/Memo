#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class MyStack {
private:
    int size;
    int top;
    int* data;
    
public:
    MyStack(int size = 1000) {
        this->size = size;
        top = -1;
        data = (int*)malloc(sizeof(int) * size);
    }
    ~MyStack() {
        free(data);
    }
    bool is_empty() {
        return (top == -1);
    }
    bool is_full() {
        return (top == size-1);
    }
    void push(int data) {
        if (is_full()) {
            printf("push error\n");
            return;
        }
        this->data[++top] = data;
    }
    int pop() {
        if (is_empty()) {
            printf("pop error\n");
            return 0;
        }
        return data[top--];
    }
    int peek() {
        if (is_empty()) {
            printf("peek error\n");
            return 0;
        }
        return data[top];
    }
};

int op_rank(char op) {
    switch (op) {
        case '(': case ')': return 0;
        case '+': case '-': return 1;
        case '*': case '/': return 2;
    }
    return -1;
}

void infix_to_postfix(const char* infix, char* postfix) {
    MyStack ops;
    int len = strlen(infix);
    int pos = 0;
    
    for (int i = 0; i < len; i++) {
        switch (infix[i]) {
            case '+':
            case '-':
            case '*':
            case '/':
                while (!ops.is_empty() && op_rank(ops.peek()) >= op_rank(infix[i])) {
                    // 우선순위가 높은 연산자가 있으면 먼저 계산
                    postfix[pos++] = ops.pop();
                }
                ops.push(infix[i]);
                break;
                
            case '(':
                ops.push(infix[i]);
                break;
                
            case ')':
                while (ops.peek() != '(') {
                    // 여는 괄호까지 모두 출력 
                    postfix[pos++] = ops.pop();
                }
                ops.pop();
                break;
                
            default:
                postfix[pos++] = infix[i];
        }
    }
    
    // 남은 연산자 모두 출력
    while (!ops.is_empty()) {
        postfix[pos++] = ops.pop();
    }
    
    postfix[pos] = 0; // NULL 문자 
}

bool is_number(char x) {
    return (x >= '0' && x <= '9');
}

int eval_postfix(const char* postfix) {
    MyStack nums;
    int len = strlen(postfix);

    for (int i = 0; i < len; i++) {
        if (is_number(postfix[i])) {
            nums.push(postfix[i] - '0');
        } else {
            int num1, num2;
            num2 = nums.pop(); // 두번째 숫자부터 꺼냄 
            num1 = nums.pop();
            switch (postfix[i]) {
                case '+': nums.push(num1 + num2); break;
                case '-': nums.push(num1 - num2); break;
                case '*': nums.push(num1 * num2); break;
                case '/': nums.push(num1 / num2); break;
            }
        }
    }
    
    return nums.pop();
}

// 테스트 
bool test_all() {
    const char* infix_exp[] = {
        "3+4+2",
        "3*4+2",
        "3+4*2",
        "(2+3)*4-9/3",
        "((8/2)-3)+(3*2)"
    };
    const char* postfix_exp[] = {
        "34+2+",
        "34*2+",
        "342*+",
        "23+4*93/-",
        "82/3-32*+"
    };
    const int result[] = {
        9,
        14,
        11,
        17,
        7
    };
    
    int err = 0;
    for (int i = 0; i < sizeof(result) / sizeof(int); i++) {
        char temp[100];
        infix_to_postfix(infix_exp[i], temp);
        if (strcmp(postfix_exp[i], temp)) {
            printf("error: infix_to_postfix(\"%s\")\n", infix_exp[i]);
            err++;
        }
        
        int value = eval_postfix(postfix_exp[i]);
        if (result[i] != value) {
            printf("error: eval_postfix(\"%s\") = %d\n", postfix_exp[i]);
            err++;
        }
    }
    
    if (err) {
        printf("test: error.\n");
    } else {
        printf("test: finished. no error.\n");
    }
}

int main() {
    test_all();
    
    char infix_exp[100] = { 0, };
    printf("중위 표기식 : ");
    scanf("%s", infix_exp);

    char postfix_exp[100] = { 0, };
    infix_to_postfix(infix_exp, postfix_exp);
    printf("후위 표기식 : %s\n", postfix_exp);
     
    int result;
    result = eval_postfix(postfix_exp);
    printf("결과값 : %d\n", result);
    
    return 0;
}
