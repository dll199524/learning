
from lexer import *
from parse import *


def run(fn, text):
    lexer = Lexer(fn, text)
    tokens, error = lexer.make_tokens()
    print(tokens)
    parse = Parse(tokens)
    ast = parse.parse()
    return ast.node, ast.error
