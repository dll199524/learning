from tokens import *
from position import *
from error import *
from ast_node import *


"""
语法解析结果类
"""


class ParseResult(object):
    def __init__(self):
        self.error = None
        self.node = None

    def success(self, node):
        self.node = node
        return self

    def failure(self, error):
        self.error = error
        return self

    def register(self, res):
        if isinstance(res, ParseResult):
            if res.error:
                self.error = res.error
            return res.node
        return res


"""
语法解析器
"""


class Parse(object):
    def __init__(self, tokens:Token):
        self.tokens = tokens
        self.token_idx = -1
        self.advance()

    def advance(self):
        self.token_idx += 1
        if self.token_idx < len(self.tokens):
            self.current_token:Token = self.tokens[self.token_idx]
        return self.current_token

    """
    expr -> term (( PLUS | MINUS ) term)*
    term -> factor (MUL | DIV ) factor)*
    factor  -> INT | FLOAT
            -> ( PLUS | MINUS ) factor
            -> LPAREN expr RPAREN
    """

    def parse(self):
        res = self.expr()
        if not res.error and self.current_token.type != TT_EOF:
            return res.failure(InvalidSyntaxError(self.current_token.pos_start,
                                                  self.current_token.pos_end, "Expected '+', '-', '*' or '/'"))
        return res

    def expr(self):
        return self.bin_op(self.term, (TT_PLUS, TT_MINUS))

    def term(self):
        return self.bin_op(self.factor, (TT_MUL, TT_DIV))

    def bin_op(self, fuc, ops):
        res = ParseResult()
        left = res.register(fuc())
        while self.current_token.type in ops:
            op_token = self.current_token
            res.register(self.advance())
            right = res.register(fuc())
            left = BinOpNode(left, op_token, right)
        return res.success(left)

    def factor(self):
        res = ParseResult()
        token = self.current_token
        if token.type in (TT_INT, TT_FLOAT):
            res.register(self.advance())
            return res.success(NumberNode(token))

        elif token.type in (TT_PLUS, TT_MINUS):
            res.register(self.advance())
            factor = res.register(self.factor())
            if res.error:
                return res
            return res.success(UnaryOpNode(token, factor))

        elif token.type == TT_LPAREN:
            res.register(self.advance())
            expr = res.register(self.expr())
            if res.error:
                return res
            if self.current_token == TT_RPAREN:
                res.register(self.advance())
                return res.success(expr)
            else:
                return res.failure(InvalidSyntaxError(self.current_token.pos_start,
                                                      self.current_token.pos_end, "Expected '+', '-', '*' or '/'"))
