"""
code -> 解释器 -> 结果
code -> 编译器 -> 可执行文件(exe) -> 程序运行的结果
"""


from error import RTError


class RTRResult(object):
    def __init__(self):
        self.value = None
        self.error = None

    def success(self, value):
        self.value = value
        return self

    def failure(self, error):
        self.error = error
        return self

    def register(self, res):
        if res.error:
            return res.error
        else:
            return res.value


class Number(object):
    def __init__(self, value):
        self.value = value
        self.set_pos()  # 报错的位置
        self.set_context()  # 方便定义错误，运行时的上下文

    def set_pos(self, pos_start, pos_end):
        self.pos_start = pos_start
        self.pos_end = pos_end
        return self

    def set_context(self, context):
        self.context = context
        return self

    def added_by(self, other):
        if isinstance(other, Number):
            return Number(self.value + other.value).set_context(self.context), None

    def subed_by(self, other):
        if isinstance(other, Number):
            return Number(self.value - other.value).set_context(self.context), None

    def multed_by(self, other):
        if isinstance(other, Number):
            return Number(self.value * other.value).set_context(self.context), None

    def dived_by(self, other):
        if isinstance(other, Number):
            if other.value == 0:
                return None, RTError(other.pos_start, other.pos_end, "分母不能为零", self.context)
            return Number(self.value / other.value).set_context(self.context), None
