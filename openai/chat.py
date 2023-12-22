# import os
# from openai import OpenAI
#
# client = OpenAI(
#     api_key = ''
# )
# messages = [ {"role": "system", "content": "You are a intelligent assistant."} ]
#
#
# while True:
# 	message = input("User : ")
# 	if message:
# 		messages.append({"role": "user", "content": message})
# 		chat = client.chat.completions.create(
# 			model="gpt-3.5-turbo",
#             messages=messages,
# 		)
#
# 	reply = chat.choices[0].message.content
# 	print(f"ChatGPT: {reply}")
#
# 	messages.append({"role": "assistant", "content": reply})

from openai import OpenAI
client = OpenAI(api_key = '')

completion = client.chat.completions.create(
  model="gpt-3.5",
  messages=[
    {"role": "system", "content": "You are a poetic assistant, skilled in explaining complex programming concepts with creative flair."},
    {"role": "user", "content": "Compose a poem that explains the concept of recursion in programming."}
  ]
)

print(completion.choices[0].message)
