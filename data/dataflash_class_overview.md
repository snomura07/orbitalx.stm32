# DataFlashクラス概要

## 目的
`DataFlash` クラスは、STM32内蔵Flashを「設定パラメータ保存領域」として使うための薄いラッパーです。

主な責務:
- 指定アドレスへデータを書き込む
- 指定アドレスからデータを読み出す
- Flashのunlock/lock、ページ消去、double word書き込みを隠蔽する
- アドレス範囲チェックを行う

---

## 保存領域の前提
- 開始アドレス: `DATAFLASH_START_ADDR`（`MasterDefine.h`）
- サイズ: `5 * 1024` bytes（`FlashSize`）
- 書き込み単位:
  - API上は `uint16_t` 配列
  - 実Flash書き込みは `FLASH_TYPEPROGRAM_DOUBLEWORD`（64bit）

---

## 公開メソッド

## `bool writeData(uint32_t address, const uint16_t* data, size_t length)`
指定アドレスに `uint16_t` 配列を書き込みます。

現在の実装フロー:
1. 入力チェック（null、length==0）
2. アドレス範囲チェック（`isAddressValid`）
3. 書き込み対象が1ページ内に収まるか確認
4. 対象ページ全体をRAMへ退避
5. 退避データ内の対象領域だけ更新
6. Flash unlock
7. 対象ページを消去
8. ページ全体をdouble word単位で再書き込み
9. Flash lock

ポイント:
- Flashはページ消去が必要なので、項目単位更新でも内部ではページ単位の再書き込みになる
- 同ページ上の他データを保護するため、read-modify-write方式になっている

## `bool readData(uint32_t address, uint16_t* data, size_t length) const`
指定アドレスから `uint16_t` 配列を読み出します。

フロー:
1. 入力チェック
2. アドレス範囲チェック
3. 64bitずつ読み、16bit×4要素に展開して出力

---

## 非公開メソッド

## `bool unlockFlash() const`
`HAL_FLASH_Unlock()` を呼び、Flash操作を許可。

## `bool lockFlash() const`
`HAL_FLASH_Lock()` を呼び、Flash操作を終了。

## `bool eraseSector(uint32_t address)`
指定アドレスが属するページを1ページ消去。
- `FLASH_EraseInitTypeDef` を構成し `HAL_FLASHEx_Erase()` を呼ぶ

## `bool writeDoubleWord(uint32_t address, uint64_t data) const`
64bit単位でFlashへプログラム。
- `HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, ...)`

## `bool isAddressValid(uint32_t address, size_t size) const`
アクセス範囲が保存領域内かを判定。

---

## メンバ定数
- `FlashStartAddress`: 保存領域開始アドレス
- `FlashSize`: 保存領域サイズ
- `FlashBaseAddress`: MCU Flash全体のベース（`0x08000000`）

---

## 使う側（Parameterクラス）との関係
`Parameter` クラスは、各パラメータ（PID, センサ参照値など）を固定アドレスへ配置し、
実際の保存/読出しは `DataFlash::writeData/readData` に委譲しています。

つまり:
- パラメータの意味づけ・アドレス管理: `Parameter`
- Flash操作の実処理: `DataFlash`

