# language: ru
import os
import sys
import subprocess
from behave import given, when, then, step

class Buffer(object):

    def __init__(self, file_good, file_bad, file_notfound, console_error1, console_error2, console_error3, console_result):
        self.file_good = file_good
        self.file_bad = file_bad
        self.file_notfound = file_notfound
        self.console_error1 = console_error1
        self.console_error2 = console_error2
        self.console_error3 = console_error3
        self.console_result = console_result

@given('подготовили правильный текстовый файл {file}')
def step_impl(context, file: str):
    Buffer.file_good = file
    pass

@given('подготовили неправильный текстовый файл {file}')
def step_impl(context, file: str):
    Buffer.file_bad = file
    pass

@given('придумали несуществующий текстовый файл {file}')
def step_impl(context, file: str):
    Buffer.file_notfound = file
    pass

@when('запускаем приложение count_pairs с недостаточным числом аргументов')
def step_impl(context):
    result_console = os.popen('count_pairs.exe ' + Buffer.file_good + ' налоги 1')
#    result_console = os.popen('./a.out ' + Buffer.file_good + ' налоги 1')
    Buffer.console_error1 = result_console.read()
    result_console.close()
    pass

@when('запускаем приложение count_pairs с указанием этого файла')
def step_impl(context):
    result_console = os.popen('count_pairs.exe ' + Buffer.file_bad + ' налоги России 1')
#    result_console = os.popen('./a.out ' + Buffer.file_bad + ' налоги России 1')
    Buffer.console_error2 = result_console.read()
    result_console.close()
    pass

@when('запускаем приложение count_pairs с указанием несуществующего файла')
def step_impl(context):
    result_console = os.popen('count_pairs.exe ' + Buffer.file_notfound + ' налоги России 1')
#    result_console = os.popen('./a.out ' + Buffer.file_notfound + ' налоги России 1')
    Buffer.console_error3 = result_console.read()
    result_console.close()
    pass

@when('ищем пару слов {words} на расстояниии, не превышающем {dist} слов')
def step_impl(context, words: str, dist: int):
    word = words.split()
    first_word = word[0].replace('"', '')
    second_word = word[1].replace('"', '')
    result_console = os.popen('count_pairs.exe ' + Buffer.file_good + ' ' + first_word + ' ' + second_word + ' ' + dist)
#    result_console = os.popen('./a.out ' + Buffer.file_good + ' ' + first_word + ' ' + second_word + ' ' + dist)
    Buffer.console_result = result_console.read()
    result_console.close()
    pass

@then('получаем сообщение об ошибке о неправильном использовании приложения')
def step_impl(context):
    assert Buffer.console_error1 == 'Error: Usage: count_pairs.exe [path to the txt file] [first word] [second word] [max length between words]\n'

@then('получаем сообщение об ошибке о неправильном расширении файла')
def step_impl(context):
    assert Buffer.console_error2 == 'Error: file format must be .txt\n'

@then('получаем сообщение об ошибке об отсутствии файла')
def step_impl(context):
    assert Buffer.console_error3 == 'Error: no such file or path\n'

@then('находим {rez} такую пару в текстовом файле')
def step_impl(context, rez: int):
    assert rez == Buffer.console_result[-2]