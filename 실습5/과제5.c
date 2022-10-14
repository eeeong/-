#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define STACK_MAX_SIZE 30

typedef enum
{
    lparen, // '('
    rparen, // ')'
    plus,   // '+'
    minus,  // '-'
    times,  // '*'
    divide, // '/'
    mod,    // '%'
    eos,    // ' '
    operand // 숫자
} precedence;

// precedence형 스택에 대한 push와 pop
void pushP(precedence *stack, int *stack_top, precedence item)
{
    if (*stack_top == STACK_MAX_SIZE - 1)
    {
        printf("스택이 꽉 찼어요! 돌아갓!\n");
        return;
    }
    stack[++(*stack_top)] = item;
}
precedence popP(precedence *stack, int *stack_top)
{
    if (*stack_top == -1)
    {
        printf("스택이 비었어요! 돌아갓!\n");
        exit(1);
    }
    return stack[(*stack_top)--];
}

// int형 스택에 대한 push와 pop
void pushI(int *stack, int *stack_top, int item)
{
    if (*stack_top == STACK_MAX_SIZE - 1)
    {
        printf("스택이 꽉 찼어요! 돌아갓!\n");
        return;
    }
    stack[++(*stack_top)] = item;
}
int popI(int *stack, int *stack_top)
{
    if (*stack_top == -1)
    {
        printf("스택이 비었어요! 돌아갓!\n");
        exit(1);
    }
    return stack[(*stack_top)--];
}

precedence getToken(char *expr, char *symbol, int *n)
{
    *symbol = expr[(*n)++];
    switch (*symbol)
    {
    case '(':
        return lparen;
    case ')':
        return rparen;
    case '+':
        return plus;
    case '-':
        return minus;
    case '*':
        return times;
    case '/':
        return divide;
    case '%':
        return mod;
    case '\0':
        return eos;
    default:
        return operand;
    }
}

char printToken(precedence token)
{
    switch (token)
    {
    case lparen:
        return '(';
    case rparen:
        return ')';
    case plus:
        return '+';
    case minus:
        return '-';
    case times:
        return '*';
    case divide:
        return '/';
    case mod:
        return '%';
    case eos:
        return '\0';
    default:
        return '.'; //숫자는 어떻게?
    }
}

//연산자 Stack을 출력하기 위해 연산자 문자열로 변환해 반환하는 함수
char *printStack(precedence *stack, int stack_top)
{
    char *print_stack;
    print_stack = (char *)malloc(STACK_MAX_SIZE * sizeof(char));
    int i;
    for (i = 0; i <= stack_top; i++)
        print_stack[i] = printToken(stack[i]);
    print_stack[i] = printToken(eos);
    return print_stack;
}

// infix -> postfix
void postfix(char *expr, char *new_expr)
{
    int isp[] = {0, 19, 12, 12, 13, 13, 13, 0};  // stack에 저장된 연산자 우선순위
    int icp[] = {20, 19, 12, 12, 13, 13, 13, 0}; //입력 연산자의 우선순위
    precedence stack[STACK_MAX_SIZE], token;
    int stack_top = -1, n = 0, new_idx = -1;
    char symbol;

    printf("[ Infix to Postfix ]\n");
    printf("  %-7s|  %-20s|  %-5s|  %-8s\n", "Token", "Stack", "Top", "Output");

    for (token = getToken(expr, &symbol, &n); token != eos; token = getToken(expr, &symbol, &n))
    {
        if (token == operand)
            new_expr[++new_idx] = symbol;
        else if (token == rparen)
        {
            while (stack[stack_top] != lparen)
                new_expr[++new_idx] = printToken(popP(stack, &stack_top));
            popP(stack, &stack_top); //스택 안의 '(' 제거
        }
        else
        {
            while (isp[stack[stack_top]] >= icp[token]) //연산자 우선순위에 따라 pushP or popP
                new_expr[++new_idx] = printToken(popP(stack, &stack_top));
            pushP(stack, &stack_top, token);
        }
        printf("    %-5c|  %-20s|   %-4d|  %s\n", symbol, printStack(stack, stack_top), stack_top, new_expr);
    }
    new_expr[++new_idx] = printToken(eos);
    printf("*** Postfix 변환 완료! ***\nPostfix : ");
    for (int i = 0; i < new_idx; i++)
        printf("%c ", new_expr[i]);
    printf("\n\n");
}

// postfix -> 연산 결과 반환
int eval(char *expr)
{
    precedence token;
    char symbol;
    int stack[STACK_MAX_SIZE];
    int n = 0, stack_top = -1, op1, op2;

    printf("Postfix : ");
    for (int i = 0; expr[i] != printToken(eos); i++)
        printf("%c ", expr[i]);
    printf("\n[ Eval of Postfix ]\n");
    printf("  %-7s|  %-30s|  %s\n", "Token", "Stack", "Top");

    token = getToken(expr, &symbol, &n);
    while (token != eos)
    {
        if (token == operand)
            pushI(stack, &stack_top, symbol - '0'); //스택에 피연산자 삽입
        else
        {
            op2 = popI(stack, &stack_top);
            op1 = popI(stack, &stack_top);
            switch (token)
            {
            case plus:
                pushI(stack, &stack_top, op1 + op2);
                break;
            case minus:
                pushI(stack, &stack_top, op1 - op2);
                break;
            case times:
                pushI(stack, &stack_top, op1 * op2);
                break;
            case divide:
                pushI(stack, &stack_top, op1 / op2);
                break;
            case mod:
                pushI(stack, &stack_top, op1 % op2);
            default:
                break; //나중에 응용
            }
        }
        printf("    %-5c|  ", symbol);
        for (int i = 0; i <= stack_top; i++)
            printf("%-3d", stack[i]);
        for (int i = 0; i < STACK_MAX_SIZE / 3 - stack_top - 1; i++)
            printf("%3c", ' ');
        printf("|   %d\n", stack_top);

        token = getToken(expr, &symbol, &n);
    }
    return popI(stack, &stack_top);
}

int main(void)
{
    char expr[STACK_MAX_SIZE], new_expr[STACK_MAX_SIZE];
    int result;

    printf("Infix 수식 입력 >> ");
    scanf("%s", expr); // infix 수식 입력받아 expr에 저장

    postfix(expr, new_expr); // infix -> postfix
    result = eval(new_expr);
    printf("*** 연산 완료! ***\nEval : %d\n", result);

    return 0;
}