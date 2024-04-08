#include <iostream>
#include <stack>
#include <cmath>
#include <cstring>

using namespace std;

int prioridadFuera(char c) {
    switch(c) {
        case '^':
            return 4;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        case '(':
            return 5;
    }
    return -1;
}

int prioridadDentro(char c) {
    switch(c) {
        case '^':
            return 3;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        case '(':
            return 0;
    }
    return -1;
}

char* posfija(char infija[50]) {
    int tam = strlen(infija), j = 0;
    char* pos = new char[tam + 1]; // Reservar espacio para la cadena pos
    stack<char> p1;
    
    for(int i = 0; i < tam; i++) {
        char c = infija[i];
        
        if(c >= '0' && c <= '9') {
            // Si es un dígito, copiamos los dígitos seguidos
            while(i < tam && (infija[i] >= '0' && infija[i] <= '9')) {
                pos[j++] = infija[i++];
            }
            pos[j++] = ' '; // Agregamos un espacio después del número
            i--; // Retrocedemos el índice para evitar perder el siguiente carácter
        } else {
            if(prioridadFuera(c) != -1) {
                if(p1.empty()) {
                    p1.push(c);
                } else {
                    if(prioridadFuera(c) > prioridadDentro(p1.top())) {
                        p1.push(c);
                    } else {
                        while(!p1.empty() && prioridadFuera(c) <= prioridadDentro(p1.top())) {
                            pos[j++] = p1.top();
                            p1.pop();
                        }
                        p1.push(c);
                    }
                }
            } else {
                while(p1.top() != '(') {
                    pos[j++] = p1.top();
                    p1.pop();
                }
                p1.pop();
            }
        }   
    }
    
    while(!p1.empty()) {
        pos[j++] = p1.top();
        p1.pop();
    }
    pos[j] = '\0'; // Agregar el carácter nulo al final de la cadena
    return pos;
}

double evaluarExpresion(char *cadena) {
    char* expresion = posfija(cadena);
    stack<double> pila;
    int len = strlen(expresion);

    for (int i = 0; i < len; i++) {
        if (isdigit(expresion[i])) {
            double num = 0;
            while (isdigit(expresion[i])) {
                num = num * 10 + (expresion[i] - '0');
                i++;
            }
            pila.push(num);
            i--; // Retrocedemos el índice para no perder el siguiente carácter
        } else if (isspace(expresion[i])) {
            continue;
        } else {
            double op2 = pila.top();
            pila.pop();
            double op1 = pila.top();
            pila.pop();

            switch (expresion[i]) {
                case '+': pila.push(op1 + op2); break;
                case '-': pila.push(op1 - op2); break;
                case '*': pila.push(op1 * op2); break;
                case '/': pila.push(op1 / op2); break;
                case '^': pila.push(pow(op1, op2)); break;
                default:
                    cerr << "Operador no válido: " << expresion[i] << endl;
                    return 0.0;
            }
        }
    }

    return pila.top();
}

int main() {
    char cadena[] = "1-3";
    cout << "Resultado: " << evaluarExpresion(cadena) << endl;
    return 0;
}
