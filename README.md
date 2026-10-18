# CCU Compiler-proj
紀錄一些project的東西

涵蓋 Flex進行詞法分析（Scanner）、 Bison 進行語法分析（Parser）、 C 語言 建構AST並走訪，轉譯為 SPIM 模擬器 可執行的 MIPS Assembly。

---

## 專案階段簡述

| 階段 | 簡述 |
| :--- |  :--- |
| **Lexical Analysis**  |  Flex 定義RE，識別keyword、ID、、const、Operator等並傳回對應 Token。 |
| **Syntax Analysis**  | Bison 定義CFG，處理運算子優先權與結合性，驗證宣告、算術運算、條件分支與迴圈語法結構。 |
| **AST**  | 定義 `tree_node` 結構與節點build_function，建立 AST |
| **MIPS Code Generation** | 遞迴走訪 AST 並配置register管理機制，轉譯變數、算術與邏輯表達式、控制流程及系統呼叫等為MIPS語言。 |


---

## 開發與執行環境

* **實作語言與工具**：C 、GNU Flex、GNU Bison、
* **Target ISA**：MIPS32 Assembly
