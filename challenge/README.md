Twoim zdaniem jest zdefiniować dwa endpointy(switch, status).
Odpytanie endpointu 'switch' spowoduje wyłączenie/wyłącznie przelącznika jak i zwrócenie odpowiedniego statusu:
curl http://<ip>/switch
{"Status": "Off"} lub {"Status": "On"}

Dodatkowo musisz zdefiniować endpoint "status", pod którym będzie można sprawdzić aktualny status przełącznika:
curl http://<ip>/status
musi zwrócić:
{"Status": "On"} lub {"Status": "Off"}

Dodatakwo przy restarcie urządzenia musimy mieć pewność, że przełącznik jest wyłączony (dioda na przełączniku nie świeci).
