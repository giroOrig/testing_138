#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;


string obtenerPrimeraParte(string pedido, string delimitador);

string obtenerPrimeraParte(string pedido, string delimitador) {
	size_t posicion = 0;
	string primeraParte;
	while ((posicion = pedido.find(delimitador)) != string::npos) {
		primeraParte = pedido.substr(0, posicion);
		pedido.erase(0, posicion + delimitador.length());
	}
	return primeraParte;
}

string obtenerSegundaParte(string pedido, string delimitador);

string obtenerSegundaParte(string pedido, string delimitador) {
	auto start = 0;
	auto end = pedido.find(delimitador);
	while (end != string::npos)
	{
		start = end + delimitador.length();
		end = pedido.find(delimitador, start);
	}
	return pedido.assign(pedido.substr(start, end));
}

unordered_map<string, string> getTransactionData(string uri);

unordered_map<string, string> getTransactionData(string uri) {
	unordered_map<string, string> mapa_clave_valor;
	
	size_t comienzo, posicion = 0;
	string clave_valorP;
	string del_C_V = "=";
	string del_param = "&";
	

	while ((comienzo = uri.find_first_not_of(del_param, posicion)) != string::npos) {
		posicion = uri.find_first_of(del_param, comienzo + 1);
		clave_valorP = uri.substr(comienzo, posicion - comienzo);

		string valor_llave = obtenerPrimeraParte(clave_valorP, del_C_V);
		string valor_valor = obtenerSegundaParte(clave_valorP, del_C_V);
		mapa_clave_valor.insert({ valor_llave, valor_valor });
	}
	return mapa_clave_valor;
}

int main() {


	string url = "bitcoin=175tWpb8K1S7NmH4&amount=50&label=Luke-Jr&message=Donation";
	unordered_map<string, string> t_data = getTransactionData(url);
	

	cout << "address: " << t_data["bitcoin"] << endl;
	cout << "amount: " << t_data["amount"] << endl;
	cout << "name: " << t_data["label"] << endl;
	cout << "message: " << t_data["message"] << endl;
	system("pause");
	return 0;
}
