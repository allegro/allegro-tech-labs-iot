Głównym twoim zdaniem jest zdefiniować dwa endpointy(switch, status), które będą włączać/wyłączać przełączik.
Odpytanie powyższego endpointu spowoduje wyłączenie/wyłącznie przelącznika jak i zwrócenie odpowiedniego statusu:
curl http://<ip>/switch
{"Status": "Off"} lub {"Status": "On"}

Dodatkowo musisz zdefiniować endpoint "stat" pod, którym będzie można sprawdzić status przełącznika:
curl http://<ip>/status
{"Status": "On"} lub {"Status": "Off"}

Dodatakwo przy restarcie urządzenia, musimy mieć pewność, że przełącznik jest wyłączony.