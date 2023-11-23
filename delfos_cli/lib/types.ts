declare global {
  interface Window {
    _db_query(query: string): Promise<string>,
    _storage_set(key: string, value: any): Promise<string>,
    _storage_get(key: string): Promise<string>,
    _storage_del(key: string): Promise<string>
    _window_set_position(x: number, y: number): Promise<string>,
    _window_set_size(width: number, height: number): Promise<string>,
    _window_maximize(): Promise<string>,
    _window_minimize(): Promise<string>,
    _window_restore(): Promise<string>,
    delfos: DelfosWebview
  }
}

export type SQLiteValues = string | number;

export type DelfosStorage = {
  set(key: string, value: any): Promise<string>,
  get(key: string): Promise<string>,
  del(key: string): Promise<string>
}

export type DelfosDatabase = {
  query(query: string): Promise<any>,
  select(table: string, columns?: string[] | string, where?: string): Promise<any>,
  insert(table: string, values: Array<string|number>[] | string[], columns?: string[] | string): Promise<any>
  delete(table: string, where?: string): Promise<any>
}

export interface DelfosWindow {
  setPosition(x: number, y: number): Promise<string>,
  setSize(width: number, y: number): Promise<string>,
  maximize(): Promise<string>,
  restore(): Promise<string>,
  minimize(): Promise<string>,
  close(): Promise<string>
}
 
export interface DelfosWebview {
  database: DelfosDatabase,
  storage: DelfosStorage,
  window: DelfosWindow
}
