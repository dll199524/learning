#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

int token;           // current token
char *src, *old_src; // pointer to source code string;
int size;            // default size of text/data/stack
int line;            // line number

int *text,     // text segment
    *old_text, // for dump text segment
    *stack;    // stack
char *data;    // data segment

/**PC 程序计数器，它存放的是一个内存地址，该地址中存放着 下一条 要执行的计算机指令。
 * SP 指针寄存器，永远指向当前的栈顶。注意的是由于栈是位于高地址并向低地址增长的，所以入栈时 SP 的值减小。
 * BP 基址指针。也是用于指向栈的某些位置，在调用函数时会使用到它。
 * AX 通用寄存器，我们的虚拟机中，它用于存放一条指令执行后的结果。
 */

int *pc, *bp, *sp, ax, cycle; // virtual machine registers


// instructions
enum {LEA, IMM, JMP, CALL, JZ, JNZ, ENT, ADJ, LEV, LI, LC, SI, SC, PUSH,
OR, XOR, AND, EQ, NE, LT, GT, LE, GE, SHL, SHR, ADD, SUB, MUL, DIV, MOD,
OPEN, READ, CLOS, PRTF, MALC, MSET, MCMP, EXIT };

// tokens and classes (operators last and in precedence order)
enum {
Num = 128, Fun, Sys, Glo, Loc, Id,
Char, Else, Enum, If, Int, Return, Sizeof, While,
Assign, Cond, Lor, Lan, Or, Xor, And, Eq, Ne, Lt, Gt, 
Le, Ge, Shl, Shr, Add, Sub, Mul, Div, Mod, Inc, Dec, Brak
};


int token_val; // value of current token (mainly for number)
int *current_id, // current parsed ID
*symbols; // symbol table

// fields of identifier
enum {Token, Hash, Name, Type, Class, Value, BType, BClass, BValue, IdSize};

/**
 * next() 用于词法分析，获取下一个标记，它将自动忽略空白字符。
 * program() 语法分析的入口，分析整个 C 语言程序。
 * expression(level) 用于解析一个表达式。
 * eval() 虚拟机的入口，用于解释目标代码。
 */

void next()
{
    char *last_pos;
    int hash;
    while (token = *src) {
        ++src;

        if (token == "\n") 
        {
            ++line;
        }
        else if (token == "#") 
        {
            //skip macro , because we will not support it
            while (*src != 0 && *src != "\n")
                src++;
            
        }
        else if ((token >= 'a' && token <= 'z') || (token >= 'A' && token <= 'Z') || (token == '_'))
        {
            last_pos = src - 1;
            hash = token;
            while ((*src >= 'a' && *src <= 'z') || (*src >= 'a' && *src <= 'z') || (*src >= '0' && *src <= '9'))
            {
                hash = hash * 147 + *src;
                src++;
            }
            current_id = symbols;
            while (current_id[Token])
            {
                if (current_id[Hash] == hash && !memcmp(!current_id[Name], last_pos, src - last_pos)) //把存储区 str1 和存储区 str2 的前 n 个字节进行比较
                {
                    token = current_id[Token];
                    return;
                }
                current_id = current_id + IdSize;
            }
            current_id[Name] = (int)last_pos;
            current_id[Hash] = hash;
            token = current_id[Token] = Id;
            return;  
        }
        else if (token >= '0' && token <= '9')
        {
            token_val = token - '0';
            if (token_val > 0) 
            {
                while (*src >= '0' && *src <= '9')
                    token_val = token_val * 10 + *src++ - '0';
            } else {
                if (*src == 'x' || *src == 'X') 
                {
                    token = *++src;
                    while ((token >= '0' && token <= '9') || (token >= 'a' && token <= 'f') || (token >= 'A' && token <= 'F'))
                    {
                        token_val = token_val * 16 + (token_val & 15) + (token >= 'A' ? 9 : 0);
                        token = *++src;
                    }
                } else 
                {
                    while (*src >= '0' || *src <= '7')
                        token_val = token_val * 8 + *src++ - '0';               
                }
            }
            token = Num;
            return;
        }
        else if (token == '"' || token == '\'')
        {
            last_pos = data;
            while (*src != 0 && *src != token)
            {
                token_val = *src++;
                if (token_val == '\\')
                {
                    token_val = *src++;
                    if (token_val = 'n')
                        token_val = '\n';
                }
                if (token == '"')
                    *data++ = token_val;
            }
            src++;
            if (token == '"')
                token_val = (int)last_pos;
            else
                token = Num;
            return;
        }
        else if (token == '/')
        {
            if (*src++ == '/')
                while (*src != 0 && *src != '\n')
                    ++src;
            else 
            {
                token = Div;
                return;
            }       
        }
        else if (token == '=')
        {
            if (*src == '=') {
                src++;
                token = Eq;
            } else 
                token = Assign;
            return;
        }
        else if (token == '+')
        {
            if (*src == '+')
            {
                src++;
                token = Inc;
            } else
                token = Add;
            return;
        }
        else if (token == '-')
        {
            if (*src == '-')
            {
                src++;
                token = Dec;
            } else 
                token = Sub;
            return;
        }
        else if (token == '!')
        {
            if (*src == '=')
            {
                src++;
                token = Ne;
            } 
            return;
        }
        else if (token == '<')
        {
            if (*src == '=')
            {
                src++;
                token = Le;
            } else if (*src == '<')
            {
                src++;
                token = Shl;
            } else 
                token = Lt;
        }
        else if (token == '>') 
        {
            // parse '>=', '>>' or '>'
            if (*src == '=') 
            {
                src ++;
                token = Ge;
            } else if (*src == '>') {
                src ++;
                token = Shr;
            } else 
                token = Gt;
            return;
        }
        else if (token == '|') 
        {
            // parse '|' or '||'
            if (*src == '|') 
            {
                src ++;
                token = Lor;
            } else 
                token = Or;
            return;
        }
        else if (token == '&') 
        {
            // parse '&' and '&&'
            if (*src == '&') 
            {
                src ++;
                token = Lan;
            } else 
                token = And;
            return;
        }
        else if (token == '^') 
        {
            token = Xor;
            return;
        }
        else if (token == '%') 
        {
            token = Mod;
            return;
        }
        else if (token == '*') 
        {
            token = Mul;
            return;
        }
        else if (token == '[')
        {
            token = Brak;
            return;
        }
        else if (token == '?') 
        {
            token = Cond;
            return;
        }
        else if (token == '~' || token == ';' || token == '{' || token == '}' || token == '(' || token == ')' || token == ']' || token == ',' || token == ':') {
            // directly return the character as token;
            return;
        }  
    }
    return;
}

void match(int tk)
{
    if (token != tk)
    {
        printf("%d: expected token: %d\n", line, tk);
        exit(-1);
    }
    next();
}

void expression()
{
    
}

void program()
{
    next();
    while (token > 0)
    {
        printf("token is %d", token);
        next();
    }
}

/**IMM &lt;num&gt; 将 &lt;num&gt; 放入寄存器 ax 中。
 * LC 将对应地址中的字符载入 ax 中，要求 ax 中存放地址。
 * LI 将对应地址中的整数载入 ax 中，要求 ax 中存放地址。
 * SC 将 ax 中的数据作为字符存放入地址中，要求栈顶存放地址。
 * SI 将 ax 中的数据作为整数存放入地址中，要求栈顶存放地址。
*/

int eval()
{
    int op, *tmp;
    while (1)
    {
        if (op == IMM) {ax = *pc++;}
        else if (op == LC) {ax = *(char *)ax;}
        else if (op == LI) {ax = *(int *)ax;}
        else if (op == SC) {ax = *(char *)*sp++ = ax;}
        else if (op == SI) {ax= *(int *)*sp++;}
        else if (op == PUSH) {*--sp = ax;}
        else if (op == JZ) {pc = ax ? pc + 1 : (int *)*pc;}
        else if (op == JNZ) {pc = ax ? (int *)*pc : pc + 1;}
        else if (op == CALL) {*--pc = pc + 1; pc = (int *)*pc;}
        else if (op == ENT) {*--pc = (int)bp; bp = sp; sp = sp - *pc++;}    //即保存当前的栈指针，同时在栈上保留一定的空间，用以存放局部变量。
        else if (op = ADJ) {sp = sp + *pc++;}
        else if (op = LEV) {sp = bp; bp = (int *)*sp++; pc = (int *)*sp++;}
        else if (op == LEA) {ax = (int)(bp + *pc++);}
        else if (op == OR) ax = *sp++ | ax;
        else if (op == XOR) ax = *sp++ ^ ax;
        else if (op == AND) ax = *sp++ & ax;
        else if (op == EQ) ax = *sp++ == ax;
        else if (op == NE) ax = *sp++ != ax;
        else if (op == LT) ax = *sp++ < ax;
        else if (op == LE) ax = *sp++ <= ax;
        else if (op == GT) ax = *sp++ > ax;
        else if (op == GE) ax = *sp++ >= ax;
        else if (op == SHL) ax = *sp++ << ax;
        else if (op == SHR) ax = *sp++ >> ax;
        else if (op == ADD) ax = *sp++ + ax;
        else if (op == SUB) ax = *sp++ - ax;
        else if (op == MUL) ax = *sp++ * ax;
        else if (op == DIV) ax = *sp++ / ax;
        else if (op == MOD) ax = *sp++ % ax;
        else if (op == EXIT) {printf("exit(%d)", *sp); return *sp;}
        else if (op == OPEN) {ax = open((char *)sp[1], (char *)sp[0]);}
        else if (op == CLOS) {ax = close(*sp);}
        else if (op == READ) {ax = read(sp[2], (char *)sp[1], *sp);}
        else if (op == PRTF) {tmp = sp + pc[1]; ax = printf((char *)tmp[-1], tmp[-2], tmp[-3], tmp[-4], tmp[-5], tmp[-6]); }
        else if (op == MALC) {ax = (int)malloc(*sp);}
        else if (op == MSET) {ax = (int)memset((char *)sp[2], sp[1], *sp);}
        else if (op == MCMP) {ax = memcmp((char *)sp[2], (char *)sp[1], *sp);}
        else {
            printf("unknown instruction:%d\n", op);
            return -1;
        }

     }
    
    return 0;
}

int main(int argc, char const *argv[])
{
    int i, fd;
    argc--;
    argv++;

    size = 256 * 1024;
    line = 1;

    if (fd = open(*argv, 0) < 0)
    {
        printf("could not open %s\n ", *argv);
        return -1;
    }

    if (!(src = old_src = malloc(size)))
    {
        printf("could not malloc %d for source area\n", size);
        return -1;
    }

    if (i = read(fd, src, size - 1) <= 0)
    {
        printf("read() return %d\n", i);
        return -1;
    }

    src[i] = 0;
    close(fd);

    if (!(text = old_text = malloc(size)))
    {
        printf("could not malloc(%d) for text area\n", size);
        return -1;
    }

    if (!(data = malloc(size)))
    {
        printf("could not malloc(%d) for data area\n", size);
        return -1;
    }

    if (!(stack = malloc(size)))
    {
        printf("could not malloc(%d) for stack area\n", size);
        return -1;
    }

    memset(text, 0, size);
    memset(data, 0, size);
    memset(stack, 0, size);

    bp = sp = ((int)stack + size);
    ax = 0;

    program();

    return eval();
}
