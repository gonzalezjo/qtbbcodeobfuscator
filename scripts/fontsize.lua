local fonts = {
    "Impact",
    "Comic Sans MS",
    "Times New Roman",
}

function main(message, opened)
	if opened then
		return ("[font=%s]%s"):format(fonts[math.random(#fonts)], message)
	else
		return message .. "[/font]"
	end
end