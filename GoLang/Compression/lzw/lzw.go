package main

func LZWCompress(inputText string) (result []int) {
	dictionay := make(map[string]int)
	var i int = 0
	for ; i < 256; i++ {
		dictionay[string(rune(i))] = i
	}

	var current string
	for _, ch := range inputText {
		next := current + string(ch)
		if _, exists := dictionay[next]; exists {
			current = next
		} else {
			result = append(result, dictionay[current])
			dictionay[next] = i
			i++
			current = string(ch)
		}
	}

	if current != "" {
		result = append(result, dictionay[current])
	}
	return result
}

func LZWDecompress(compressedData []int) (result string) {
	dictionay := make(map[int]string)
	var i int = 0
	for ; i < 256; i++ {
		dictionay[i] = string(rune(i))
	}

	var previous string

	for index, data := range compressedData {
		if index == 0 {
			previous = dictionay[data]
			result += previous
		} else if data < i {
			current := dictionay[data]
			result += current
			dictionay[i] = previous + string(current[0])
			i++
			previous = current
		} else if data == i {
			previous += string(previous[0])
			result += previous
			dictionay[i] = previous
			i++
		} else {
			panic("Invalid compressed data")
		}
	}

	return result
}

func main() {
	testlist := []string{
		"ABABC",
		"ABABABABABABABABABAB",
		"TOBEORNOTTOBEORTOBEORNOT",
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ",
		"AAAAAAAAAAAAAAAAAAAAAA",
		"123456789012345678901234567890",
		"",
		"A",
		"AA",
		"AAA",
		"ABA",
		"ABAB",
		"ABABA",
		"ABABAB",
		"ABABABA",
		"ABABABAB",
		"ABABABABA",
		"ABABABABAB",
		"ABABABABABA",
		"ABABABABABAB",
		"ABABABABABABA",
		"ABABABABABABAB",
		"ABABABABABABABA",
		"ABABABABABABABAB",
		"ABABABABABABABABA",
		"ABABABABABABABABAB",
		"ABABABABABABABABABA",
		"ABABABABABABABABABAB",
		"ABABABABABABABABABABA",
		"ABABABABABABABABABABAB",
		"ABABABABABABABABABABABA",
		"ABABABABABABABABABABABAB",
		"ABABABABABABABABABABABABA",
		"ABABABABABABABABABABABABAB",
		"ABABABABABABABABABABABABABA",
		"ABABABABABABABABABABABABABAB",
		"ABABABABABABABABABABABABABABA",
		"ABABABABABABABABABABABABABABAB",
		"ABABABABABABABABABABABABABABABA",
		"ABABABABABABABABABABABABABABABAB",
		"ABABABABABABABABABABABABABABABABA",
		"ABABABABABABABABABABABABABABABABAB",
		"ABABABABABABABABABABABABABABABABABA",
		"ABABABABABABABABABABABABABABABABABAB",
		"ABABABABABABABABABABABABABABABABABABA",
		"ABABABABABABABABABABABABABABABABABABAB",
		"ABABABABABABABABABABABABABABABABABABABA",
		"ABABABABABABABABABABABABABABABABABABABAB",
		"ABABABABABABABABABABABABABABABABABABABABA",
		"ABABABABABABABABABABABABABABABABABABABABAB",
		"ABABABABABABABABABABABABABABABABABABABABABA",
		"ABABABABABABABABABABABABABABABABABABABABABAB",
		"ABABABABABABABABABABABABABABABABABABABABABABA",
		"ABABABABABABABABABABABABABABABABABABABABABABAB",
		"ABABABABABABABABABABABABABABABABABABABABABABABA",
		"ABABABABABABABABABABABABABABABABABABABABABABABAB",
		"ABABABABABABABABABABABABABABABABABABABABABABABABA",
		"ABABABABABABABABABABABABABABABABABABABABABABABABAB",
		"The quick brown fox jumps over the lazy dog",
		"Lorem ipsum dolor sit amet, consectetur adipiscing elit",
		"This is a test string for LZW compression algorithm",
		"This is a test that will make sure that proper huffman code is created. To create proper huffman code there must be sufficient large string, that must contain large number of character that is repeater several time. Huffman code consist of minimum number of bits for most repeated character and maximum number of bits for most repeated character. From normal look it is clear that space is very much repeated, other puncuation is also repeated a lot. So, space and puncuation must have minimum number of bits. Other character must have maximum number of bits.",
		"This is a test",
		"This is a test string",
		"This is a test string for",
		"This is a test string for LZW",
		"This is a test string for LZW compression",
		"This is a test string for LZW compression algorithm",
		"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
	}

	for _, inputText := range testlist {
		compressedData := LZWCompress(inputText)
		decompressedData := LZWDecompress(compressedData)
		if inputText != decompressedData {
			println("Test Failed")
			println("Input Text: ", inputText)
			println("Compressed Data: ", compressedData)
			println("Decompressed Data: ", decompressedData)
			return
		}
	}
	println("All test passed")
}
