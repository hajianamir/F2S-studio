export interface Node3D {
  id: string;
  x: number;
  y: number;
  z: number;
  pressurePsi: number;
  flowGpm: number;
  kFactor?: number;
}

export interface Pipe3D {
  id: string;
  startNodeId: string;
  endNodeId: string;
  diameterInches: number;
  flowGpm: number;
  frictionLossPsi: number;
}

export interface BcfAnnotation {
  id: string;
  elementId: string;
  author: string;
  comment: string;
  timestamp: string;
  position: [number, number, number];
}

export type Language = "en" | "fa";
