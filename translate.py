first =True
with open("index.html", "r",encoding="utf-8") as f:
    html = f.read()
html = html.split("\n")
new_html =""
for i in html:
    if(first):
        new_html += "String ptr = "+f'"{i.strip()}\\n";'+"\n"
        first = False
    else:
        new_html +="ptr += "+f'"{i.strip()}\\n";'+"\n"
new_html =new_html.strip().split("\n")
new_html.pop()
new_html.append("return ptr;")
new_html = "\n".join(new_html)
with open("webserver.txt", "w",encoding="utf-8") as f:
    f.write(new_html)