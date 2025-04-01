#include "TID.h"

using namespace new_IR;

int main()
{
	string s, line;

	while (line[0] != '`')
	{
		std::getline(cin, line);
		s += line += " ";
	}

	new_ir t(s);
	const unordered_map<string, double>& um = t.get_words_map();

	vector<pair<string, double>> term(um.begin(), um.end());

	sort(term.begin(), term.end(),
		[](auto& a, auto& b) {
			return a.second > b.second;
		});;

	for (size_t i = 0; i < 5; ++i)
	{
		cout << term[i].first << ": " << term[i].second << endl;
	}

	cout << endl;

	cout << t.query("the") << " " << t.query("an");
}

/*
Example:

The Impact of Technology on Modern Society
In the21st century, technology has become an integral part of our daily lives. From smartphones to artificial intelligence, technological advancements have revolutionized the way we communicate, work, and interact with the world around us. This article explores the profound impact of technology on modern society, examining both the benefits and challenges it presents.

Communication and Connectivity

One of the most significant changes brought about by technology is the way we communicate. The advent of the internet and social media platforms has transformed communication from a slow and cumbersome process into a real-time, global phenomenon. Today, people can connect with others across the globe instantly, breaking down barriers of distance and culture. This has not only strengthened personal relationships but also facilitated international business collaborations and cultural exchanges.

However, this increased connectivity has also raised concerns about privacy and security. As more of our personal information is shared online, the risk of data breaches and identity theft has grown. Governments and corporations are increasingly focused on developing robust cybersecurity measures to protect sensitive information.

The Evolution of Work

Technology has also had a profound impact on the workplace. Automation and artificial intelligence (AI) have transformed industries, making processes more efficient and reducing the need for human labor in certain areas. While this has led to significant productivity gains, it has also raised concerns about job displacement and the future of work.

In response, there has been a growing emphasis on upskilling and reskilling workers to adapt to the changing job market. Education systems are increasingly incorporating technology-related subjects, such as coding and digital literacy, to prepare students for the demands of the modern workforce. Additionally, the rise of remote work, facilitated by advancements in communication technologies, has reshaped traditional office environments, offering greater flexibility for employees.

Entertainment and Leisure

The entertainment industry has undergone a dramatic transformation with the advent of technology. Streaming platforms like Netflix and Spotify have revolutionized how we consume music, movies, and television shows. This shift has not only provided consumers with greater choice and convenience but has also disrupted traditional media industries, leading to the decline of physical formats like CDs and DVDs.

Moreover, virtual reality (VR) and augmented reality (AR) technologies are opening up new possibilities for immersive entertainment experiences. From virtual concerts to interactive gaming, these technologies are redefining how we engage with entertainment content, offering unparalleled levels of interactivity and realism.

Environmental Considerations

While technology has brought many benefits, it has also posed significant challenges, particularly in terms of environmental sustainability. The production and disposal of electronic devices contribute to e-waste, which is a growing environmental concern. Additionally, the energy consumption of data centers and the carbon footprint of digital technologies are issues that require urgent attention.

In response, there has been a growing push towards sustainable technology solutions. Renewable energy sources, energy-efficient hardware, and recycling programs are being developed to mitigate the environmental impact of technology. Furthermore, digital technologies are being leveraged to monitor and address environmental issues, such as climate change and deforestation, offering new tools for conservation and sustainability.

The Future of Technology

As we look to the future, it is clear that technology will continue to play a central role in shaping society. Emerging technologies, such as quantum computing, blockchain, and biotechnology, hold immense potential to solve some of the world's most pressing challenges. However, realizing this potential will require careful consideration of ethical implications and a commitment to inclusive innovation.

In conclusion, technology has undeniably transformed modern society, offering numerous benefits while also presenting significant challenges. As we move forward, it is essential to strike a balance between technological advancement and social responsibility, ensuring that technology serves as a force for good in the world. By doing so, we can harness the power of technology to build a better future for generations to come.

TOP5:
technolog: 0.303373
also: 0.126003
environmental: 0.122604
communic: 0.112512
as: 0.107498
*/