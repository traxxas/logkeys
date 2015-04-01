import re
from collections import OrderedDict

keys = [
    '<AltGr>', '<CpsLk>', '<BckSp>', '<Del>', '<Esc>', '<Tab>', '<Enter>',
    '<End>','<Home>','<PgDn>','<PgUp>', '<Menu>', '<Pause>',
    '<F1>','<F2>','<F3>','<F4>','<F5>','<F6>',
    '<F7>','<F8>','<F9>','<F10>','<F11>','<F12>',
    '<LAlt>', '<LCtrl>', '<LMeta>', '<LShft>', '<RCtrl>', '<RMeta>', '<RShft>',
    '<Up>', '<Down>', '<Left>', '<Right>',
    '0','1','2','3','4','5','6','7','8','9','0',   
    'a','b','c','d','e','f','g','h','i','j','k','l','m',
    'n','o','p','q','r','s','t','u','v','w','x','y','z',
    '!','"','#','$','%','&',"'",'(',')','*','+',',','-','.','/',':',';',
    '<','=','>','?','@','[','\\',']','^','_','`','{','|','}','~',' ',
]
stats = OrderedDict(zip(keys, [0] * len(keys)))
patt = re.compile(r'(<[A-Z#]{1}[a-zA-Z0-9+]+>)')

def parse(ls):
    content = ''.join([l.split(' > ')[-1].replace('\n', '<Enter>') for l in ls])
    re.sub(r'\n', '<Enter>', content)
    funcs = re.findall(patt, content)
    alpha, replaces = re.subn(patt, '', content)
    for key in funcs:
        if key in stats:
            stats[key] += 1
    for key in alpha:
        key = key.lower()
        if key in stats:
            stats[key] += 1
    return stats


fd = open('logkeys.log', 'r')
lines = [l for l in fd if ' > ' in l]
stats = parse(lines)
print stats
